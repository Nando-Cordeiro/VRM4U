// Fill out your copyright notice in the Description page of Project Settings.


#include "VrmAudioFreqAnalysis.h"

#include "AudioMixerBlueprintLibrary.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundSubmix.h"

DEFINE_LOG_CATEGORY_STATIC(LogVrmAudioFreqAnalysis, Log, All);

// Sets default values for this component's properties
UVrmAudioFreqAnalysis::UVrmAudioFreqAnalysis()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize pointers to nullptr
	Character = nullptr;
	AudioComponent = nullptr;
	OurSubmix = nullptr;
	// Initialize a default value for the UPROPERTY variables
	EnvelopeFollowerAttackTime = 100;
	EnvelopeFollowerReleaseTime = 50;
	OpenCounterThreshold = 2;
	ClosedCounterThreshold = 5;
	PercentRange = 0.33f;
	
}

void UVrmAudioFreqAnalysis::StartAnalysis(ASkeletalMeshActor* SceneCharacter, USoundBase* Dialogue)
{
	//Getting the UPROPERTY values and setting them to the variables
	if (Character != nullptr)
	{
		Character = SceneCharacter;
	}
	if (AudioComponent != nullptr)
	{
		AudioComponent->SetSound(Dialogue);
	}
	if (OurSubmix != nullptr)
	{
		OurSubmix->EnvelopeFollowerAttackTime = EnvelopeFollowerAttackTime;
		OurSubmix->EnvelopeFollowerReleaseTime = EnvelopeFollowerReleaseTime;
	}
	EnvelopeFollowerDelegate();
}

void UVrmAudioFreqAnalysis::OnAudioPlayStateChanged(EAudioComponentPlayState PlayState) const
{
	switch (PlayState)
	{
		case PlayState == EAudioComponentPlayState::Playing:
			EnvelopeFollowerDelegate();
			break;
		case PlayState == EAudioComponentPlayState::Stopped:
			OurSubmix->StopEnvelopeFollowing(OurSubmix);
			UAudioMixerBlueprintLibrary::StopAnalyzingOutput(OurSubmix);
			break;
		case PlayState == EAudioComponentPlayState::Paused:
			UE_LOG(LogVrmAudioFreqAnalysis, Verbose,TEXT("AudioComponent is paused"));
			break;
		case PlayState == EAudioComponentPlayState::FadingIn:
			UE_LOG(LogVrmAudioFreqAnalysis, Verbose,TEXT("AudioComponent is fading in"));
			break;
		case PlayState == EAudioComponentPlayState::FadingOut:
			UE_LOG(LogVrmAudioFreqAnalysis, Verbose,TEXT("AudioComponent is fading out"));
			break;
		default: 
			UE_LOG(LogVrmAudioFreqAnalysis, Error, TEXT("AudioComponent is in an unknown state"));
	}
}

void UVrmAudioFreqAnalysis::EnvelopeFollowerDelegate() const
{
	UAudioMixerBlueprintLibrary::StartAnalyzingOutput(OurSubmix, OurSubmix, EFFTSize::Max, EFFTPeakInterpolationMethod::Linear, EFFTWindowType::Hann, 0.0f, EAudioSpectrumType::MagnitudeSpectrum);
	OurSubmix->StartEnvelopeFollowing(OurSubmix);
	OurSubmix->AddEnvelopeFollowerDelegate(OurSubmix, EnvelopeFollowerDelegateBP(Envelope));
}

FOnSubmixEnvelopeBP UVrmAudioFreqAnalysis::EnvelopeFollowerDelegateBP(const TArray<float>& Envelope) const
{
	//
	//This entire if statement can maybe be refactored
	//
	if (Envelope.IsEmpty())
	{
		UE_LOG(LogVrmAudioFreqAnalysis, Verbose,TEXT("Envelope Array is empty"));
	}
	else
	{
		//Add envelopes to chunk
		if (EnvelopeChunk.Num() == 5)
		{
			//If the array size is already 5 when going to add a new one, remove the first element
			EnvelopeChunk.RemoveAt(0);
			EnvelopeChunk.Add(Envelope[0]);
			EnvelopeChunkIndexComparison();
		}
		else
		{
			//add index 0 of envelope to envelope chunk, really only called at the beginning
			//of the program when the array hasn't reached a size of 5 yet
			EnvelopeChunk.Add(Envelope[0]);
		}
	}
	return FOnSubmixEnvelopeBP();
}

void UVrmAudioFreqAnalysis::EnvelopeChunkIndexComparison() const
{
	/* Compare the values of index 0 and 4 of the envelope chunk,
	 * it closes the morph targets if it's equal or above the threshold too. */
	if (EnvelopeChunk[4] > EnvelopeChunk[0]) {
		CounterFunction(ClosedCounter, OpenCounter, OpenCounterThreshold);
		// Begin F group comparison after this
		FGroupAnalysis(OurSubmix, PercentRange);
	} else if (EnvelopeChunk[4] == EnvelopeChunk[0]) {
		UE_LOG(LogVrmAudioFreqAnalysis, Verbose,TEXT("Envelope Chunk Index 4 is equal to Index 0"));
	} else {
		// Index 4 is less than Index 0 here
		CounterFunction(OpenCounter, ClosedCounter, ClosedCounterThreshold);
	}
}

void UVrmAudioFreqAnalysis::CounterFunction(int OppositeCounter, int CurrentCounter, int CurrentCounterThreshold) const
{
	OppositeCounter = 0;
	CurrentCounter++;
	if (CurrentCounter >= CurrentCounterThreshold)
	{
		SetMorphTargetsClosed();
	}
}

void UVrmAudioFreqAnalysis::SetMorphTargetsClosed() const
{
	for (const FName& MorphTargetName : MouthMorphTargetNames)
	{
	Character->GetSkeletalMeshComponent()->SetMorphTarget(MorphTargetName, 0.0f, true);
	}
}

void UVrmAudioFreqAnalysis::FGroupAnalysis(USoundSubmix* SubmixToAnalyze, const float PercentRange)
{
	// remember to clear everything of all arrays too
	F1FrequencyAnalysis(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, F1LargestFrequencies, SubmixToAnalyze);
	F2FrequencyAnalysis(F2FrequenciesToAnalyze, F2MagnitudesOfFrequencies, SubmixToAnalyze);
	// whatever's in the collapsed graph goes here
	SetMorphTargetValue(PercentRange, F1, F2);
}

void UVrmAudioFreqAnalysis::F1FrequencyAnalysis(TArray<float> FrequenciesToAnalyze,
	TArray<float> MagnitudesOfFrequencies, TArray<float> LargestFrequencies, USoundSubmix* SubmixToAnalyze)
{
	SpectralBandSettings(300.0f, 1000.0f, F1FrequenciesToAnalyze);
	GetMagForFreq(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, SubmixToAnalyze);
	MakeFreqMagMap(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, F1FrequencyMagnitudeMap);
	SetF1Value(F1MagnitudesOfFrequencies, F1FrequencyMagnitudeMap);
}

void UVrmAudioFreqAnalysis::F2FrequencyAnalysis(TArray<float> FrequenciesToAnalyze,
	TArray<float> MagnitudesOfFrequencies, USoundSubmix* SubmixToAnalyze)
{
	SpectralBandSettings(1000.0f, 3000.0f, F1FrequenciesToAnalyze);
	GetMagForFreq(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, SubmixToAnalyze);
	MakeFreqMagMap(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, F1FrequencyMagnitudeMap);
	SetF2Value(F1MagnitudesOfFrequencies, F1FrequencyMagnitudeMap);
}

//
// Operations that will be done during each F Analysis
//
void UVrmAudioFreqAnalysis::SpectralBandSettings(float InMinFreq, float InMaxFreq, TArray<float>& FrequenciesToAnalyze)
{
	for (const FSoundSubmixSpectralAnalysisBandSettings SettingStruct: 	UAudioMixerBlueprintLibrary::MakeFullSpectrumSpectralAnalysisBandSettings(30, InMinFreq, InMaxFreq, 10, 10))
	{
		//Add the band frequency to the array
		FrequenciesToAnalyze.Add(SettingStruct.BandFrequency);
	}
}

void UVrmAudioFreqAnalysis::GetMagForFreq(const TArray<float>& FrequenciesToAnalyze, const TArray<float>& MagnitudesOfFrequencies, USoundSubmix* SubmixToAnalyze)
{
	TArray<float> Magnitudes;
	UAudioMixerBlueprintLibrary::GetMagnitudeForFrequencies(SubmixToAnalyze, FrequenciesToAnalyze, Magnitudes, SubmixToAnalyze);
	//Set magnitudes of frequencies equal to the magnitudes array
	Magnitudes = MagnitudesOfFrequencies;
}

void UVrmAudioFreqAnalysis::MakeFreqMagMap(TArray<float>& FrequenciesToAnalyze, TArray<float>& MagnitudesOfFrequencies, TMap<float, float>& FrequencyMagnitudeMap)
{
	for (const float& FrequencyValue : FrequenciesToAnalyze)
	{
		//return the current index of the frequency array and get the corresponding in dex in the magnitudes array
		FrequencyMagnitudeMap.Add(MagnitudesOfFrequencies[FrequenciesToAnalyze.Find(FrequencyValue)], FrequencyValue);
	}
}

void UVrmAudioFreqAnalysis::SetF1Value(TArray<float>& MagnitudesOfFrequencies, TMap<float, float>& FrequencyMagnitudeMap)
{
	//execute twice
	for (int i = 0; i < 2; i++)
	{
		//Find the max of MagnitudesOfFrequencies, remove that index from it, and add that same value in the FrequencyMagnitudeMap
		MagnitudesOfFrequencies.RemoveAt(MagnitudesOfFrequencies.Find(FMath::Max(MagnitudesOfFrequencies)));
		F1LargestFrequencies.Add(FrequencyMagnitudeMap[FMath::Max(MagnitudesOfFrequencies)]);
	}
	//remove index 0 from F1LargestFrequencies then set F1 equal to the max of F1LargestFrequencies
	F1LargestFrequencies.RemoveAt(0);
	F1 = FMath::Max(F1LargestFrequencies);
}

void UVrmAudioFreqAnalysis::SetF2Value(const TArray<float>& MagnitudesOfFrequencies, TMap<float, float>& FrequencyMagnitudeMap)
{
	F2 = FrequencyMagnitudeMap[FMath::Max(MagnitudesOfFrequencies)];
}
//
//
//

void UVrmAudioFreqAnalysis::SetMorphTargetValue(const float PercentRange, const float F1Value, const float F2Value)
{
	//create a range based for loop for morph target names
	for (const FName& MorphTargetName : MouthMorphTargetNames)
	{
		switch (MorphTargetName)
		{
			case MorphTargetName == FName("Fcl_MTH_A"):
				AddToMorphTargetMap(PercentRange, F1, F2, 775.0f, 1200.0f, MorphTargetName);
				break;
			case MorphTargetName == FName("Fcl_MTH_E"):
				AddToMorphTargetMap(PercentRange, F1, F2, 575.0f, 1850.0f, MorphTargetName);
				break;
			case MorphTargetName == FName("Fcl_MTH_I"):
				AddToMorphTargetMap(PercentRange, F1, F2, 300.0f, 2350.0f, MorphTargetName);
				break;
			case MorphTargetName == FName("Fcl_MTH_O"):
				AddToMorphTargetMap(PercentRange, F1, F2, 400.0f, 700.0f, MorphTargetName);
				break;
			case MorphTargetName == FName("Fcl_MTH_U"):
				AddToMorphTargetMap(PercentRange, F1, F2, 300.0f, 750.0f, MorphTargetName);
				break;
			default: 
				UE_LOG(LogVrmAudioFreqAnalysis, Error, TEXT("Morph Target Name not found"));
		}
	}
	//over here you finally do the actual set morph target function for the skeletal mesh
}

void UVrmAudioFreqAnalysis::AddToMorphTargetMap(const float PercentRange, const float F1Value, const float F2Value, const float F1Target, const float F2Target, FName MorphTargetName)
{
	const float Value = CreateFRangeAndCheck(PercentRange, F1Value, F1Target) + CreateFRangeAndCheck(PercentRange, F2Value, F2Target);
	MorphTargetValues.Add(MorphTargetName, UKismetMathLibrary::MapRangeClamped(Value, 0.0f, 2.0f, 0.0f, 1.0f));
}

float UVrmAudioFreqAnalysis::CreateFRangeAndCheck(const float PercentRange, const float FValue, const float FTarget)
{
	const float Min = FTarget - (FTarget * PercentRange);
	const float Max = FTarget + (FTarget * PercentRange);

	//divide the value by the target, if it's greater than 1.0f
	//then return 1.0f, else return 2 minus the value
	float RangeFloat;
	
	if (const float ValueOverTarget = FValue / FTarget; ValueOverTarget > 1.0f)
	{
		 RangeFloat = 1.0f;
	}
	else
	{
		 RangeFloat = 2.0f - ValueOverTarget;
	}
	
	if (UKismetMathLibrary::InRange_FloatFloat(FValue, Min, Max, true, true))
	{
		return RangeFloat;
	}
	return 0.0f;
}




// Called when the game starts
void UVrmAudioFreqAnalysis::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVrmAudioFreqAnalysis::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

