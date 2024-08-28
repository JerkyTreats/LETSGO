// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "MetaSoundPlayerData.generated.h"

/**
 * 
 */
USTRUCT()
struct LETSGO_API FMetaSoundPlayerData
{
	GENERATED_BODY()
	
public:
	FMetaSoundPlayerData();
	explicit FMetaSoundPlayerData(USoundWave* Cue);
	FMetaSoundPlayerData(USoundWave* Cue, const float Volume);
	~FMetaSoundPlayerData();

	UPROPERTY()
	FName WaveAssetName = FName(TEXT("WaveAsset"));

	UPROPERTY()
	FName OutputVolumeName = FName(TEXT("OutputVolume"));

	UPROPERTY()
	USoundWave* WaveAsset;

	UPROPERTY()
	float OutputVolume = 1.0f;
};
