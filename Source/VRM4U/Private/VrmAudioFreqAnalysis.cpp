// Fill out your copyright notice in the Description page of Project Settings.


#include "VrmAudioFreqAnalysis.h"

#include "AudioMixerBlueprintLibrary.h"
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
	OurSubmix->AddEnvelopeFollowerDelegate(OurSubmix, EnvelopeFollowerDelegateBP());
}

FOnSubmixEnvelopeBP UVrmAudioFreqAnalysis::EnvelopeFollowerDelegateBP(const TArray<float>& Envelope)
{
	if (Envelope.IsEmpty())
	{
		UE_LOG(LogVrmAudioFreqAnalysis, Verbose,TEXT("Envelope Array is empty"));
	}
	else
	{
		
	}


		
	return FOnSubmixEnvelopeBP();
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

