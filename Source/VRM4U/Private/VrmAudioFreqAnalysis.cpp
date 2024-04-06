// Fill out your copyright notice in the Description page of Project Settings.


#include "VrmAudioFreqAnalysis.h"

#include "AudioMixerBlueprintLibrary.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/AudioComponent.h"
#include "Runtime/TraceLog/standalone_epilogue.h"
#include "Sound/SoundSubmix.h"


DEFINE_LOG_CATEGORY_STATIC(LogVrmAudioFreqAnalysis, Log, All);

// Sets default values for this component's properties
UVrmAudioFreqAnalysis::UVrmAudioFreqAnalysis()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UVrmAudioFreqAnalysis::StartAnalysis(ASkeletalMeshActor* SceneCharacter, USoundBase* Dialogue)
{
	//Getting the UPROPERTY values and setting them to the variables
	Character = SceneCharacter;
	AudioComponent->SetSound(Dialogue);
	OurSubmix->EnvelopeFollowerAttackTime = EnvelopeFollowerAttackTime;
	OurSubmix->EnvelopeFollowerReleaseTime = EnvelopeFollowerReleaseTime;
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
		FGroupAnalysis(OurSubmix);
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

void UVrmAudioFreqAnalysis::FGroupAnalysis(USoundSubmix* SubmixToAnalyze)
{
	F1FrequencyAnalysis(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, F1LargestFrequencies, SubmixToAnalyze);
	F2FrequencyAnalysis(F2FrequenciesToAnalyze, F2MagnitudesOfFrequencies, F2LargestFrequencies);
}

void UVrmAudioFreqAnalysis::F1FrequencyAnalysis(TArray<float> FrequenciesToAnalyze,
	TArray<float> MagnitudesOfFrequencies, TArray<float> LargestFrequencies, USoundSubmix* SubmixToAnalyze)
{
	SpectralBandSettings(300.0f, 1000.0f, F1FrequenciesToAnalyze);
	GetMagForFreq(F1FrequenciesToAnalyze, F1MagnitudesOfFrequencies, SubmixToAnalyze);
}

void UVrmAudioFreqAnalysis::F2FrequencyAnalysis(TArray<float> FrequenciesToAnalyze,
	TArray<float> MagnitudesOfFrequencies, TArray<float> LargestFrequencies)
{
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

