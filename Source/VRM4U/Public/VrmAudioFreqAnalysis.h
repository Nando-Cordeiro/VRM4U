// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VrmAudioFreqAnalysis.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRM4U_API UVrmAudioFreqAnalysis : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVrmAudioFreqAnalysis();

	UPROPERTY(EditAnywhere) UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere) int EnvelopeFollowerAttackTime;
	UPROPERTY(EditAnywhere) int EnvelopeFollowerReleaseTime;
	UPROPERTY(EditAnywhere) int OpenCounterThreshold;
	UPROPERTY(EditAnywhere) int ClosedCounterThreshold;
	UPROPERTY(EditAnywhere) float PercentRange;
	UPROPERTY(EditAnywhere) ASkeletalMeshActor* Character;
	UFUNCTION(BlueprintCallable) void StartAnalysis(ASkeletalMeshActor* SceneCharacter, USoundBase* Dialogue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
