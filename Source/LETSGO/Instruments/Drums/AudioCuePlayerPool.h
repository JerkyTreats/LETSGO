// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DrumsAudioCuePlayer.h"
#include "MetasoundSource.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "UObject/Object.h"
#include "AudioCuePlayerPool.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UAudioCuePlayerPool : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int CuePoolSize = 16;
	
	UPROPERTY()
	TArray<ADrumsAudioCuePlayer*> AudioCuePool;

	UFUNCTION()
	void InitializeCuePool(UMetaSoundSource* MetaSoundSource, UQuartzClockHandle* Clock, const FQuartzQuantizationBoundary& QuartzQuantizationBoundary) const;

	// UFUNCTION()
	// void Initialize(FActorSpawnParameters CuePlayerCloneParameters, UWorld* World);
	// void Initialize(FActorSpawnParameters Test);
	
	UFUNCTION()
	void PlayFreeAudioCue();
};
