// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "AudioMixerBlueprintLibrary.h"
#include "VrmAudioFreqAnalysis.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRM4U_API UVrmAudioFreqAnalysis : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVrmAudioFreqAnalysis();

	UPROPERTY(EditAnywhere) UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere) USoundSubmix* OurSubmix;

	UPROPERTY(EditAnywhere) int EnvelopeFollowerAttackTime;
	UPROPERTY(EditAnywhere) int EnvelopeFollowerReleaseTime;
	UPROPERTY(EditAnywhere) int OpenCounterThreshold;
	UPROPERTY(EditAnywhere) int ClosedCounterThreshold;
	static int OpenCounter;
	static int ClosedCounter;
	UPROPERTY(EditAnywhere) float PercentRange;
	UPROPERTY(EditAnywhere) ASkeletalMeshActor* Character;
	UFUNCTION(BlueprintCallable) void StartAnalysis(ASkeletalMeshActor* SceneCharacter, USoundBase* Dialogue);

	void OnAudioPlayStateChanged(EAudioComponentPlayState PlayState) const;
	void EnvelopeFollowerDelegate() const;
	 FOnSubmixEnvelopeBP EnvelopeFollowerDelegateBP(const TArray<float>& Envelope) const;

	static TArray<float> Envelope;
	static TArray<float> EnvelopeChunk;
	inline static const TArray<FName> MouthMorphTargetNames = { FName("Fcl_MTH_A"), FName("Fcl_MTH_E"), FName("Fcl_MTH_I"), FName("Fcl_MTH_O"), FName("Fcl_MTH_U") };

	 void EnvelopeChunkIndexComparison() const;
	 void CounterFunction(int OppositeCounter, int CurrentCounter, int CurrentCounterThreshold) const;
	void SetMorphTargetsClosed() const;

	static TArray<float> F1FrequenciesToAnalyze;
	static TArray<float> F1MagnitudesOfFrequencies;
	static TArray<float> F1LargestFrequencies;
	static TMap<float, float> F1FrequencyMagnitudeMap;
	static float F1;
	
	static TArray<float> F2FrequenciesToAnalyze;
	static TArray<float> F2MagnitudesOfFrequencies;
	static TMap<float, float> F2FrequencyMagnitudeMap;
	static float F2;
	
	//Make a TArray of TArray<float>
	// maybe not needed
	static TArray<TArray<float>> ArrayOfF1F2Arrays;

	// This is the "sequence node" in the BP graph
	static void FGroupAnalysis(USoundSubmix* SubmixToAnalyze);
	static void F1FrequencyAnalysis(TArray<float> FrequenciesToAnalyze, TArray<float> MagnitudesOfFrequencies, TArray<float> LargestFrequencies, USoundSubmix* SubmixToAnalyze);
	static void F2FrequencyAnalysis(TArray<float> FrequenciesToAnalyze, TArray<float> MagnitudesOfFrequencies, TArray<float> LargestFrequencies, USoundSubmix* SubmixToAnalyze);
	// whatever's in the collapsed graph goes here
	
	// Operations that will be done during each F Analysis
	static void SpectralBandSettings(float InMinFreq, float InMaxFreq, TArray<float>& FrequenciesToAnalyze);
	static void GetMagForFreq(const TArray<float>& FrequenciesToAnalyze, const TArray<float>& MagnitudesOfFrequencies, USoundSubmix* SubmixToAnalyze);
	static void MakeFreqMagMap(TArray<float>& FrequenciesToAnalyze, TArray<float>& MagnitudesOfFrequencies, TMap<float, float>& FrequencyMagnitudeMap);
	static void SetF1Value(TArray<float>& MagnitudesOfFrequencies, TMap<float, float>& FrequencyMagnitudeMap);
	static void SetF2Value(TArray<float>& MagnitudesOfFrequencies, TMap<float, float>& FrequencyMagnitudeMap);

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
