// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
#include "GameFramework/Actor.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "DrumsAudioCuePlayer.generated.h"

UCLASS()
class LETSGO_API ADrumsAudioCuePlayer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrumsAudioCuePlayer();

	UPROPERTY()
	bool IsSoundPlaying = false;

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY()
	UMetaSoundSource* MetaSoundSource;

	UPROPERTY()
	UQuartzClockHandle* Clock;

	UPROPERTY()
	FQuartzQuantizationBoundary QuartzQuantizationBoundary;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize(UMetaSoundSource* ParentMetaSoundSource, UQuartzClockHandle* ParentClock, FQuartzQuantizationBoundary ParentQuartzQuantizationBoundary);

	UFUNCTION()
	void Play();

	UFUNCTION()
	void PlayAndDestroy();
	
	UFUNCTION()
	void ResetAudioCue();
	
	UFUNCTION()
	void DestroyActor();
	
};
