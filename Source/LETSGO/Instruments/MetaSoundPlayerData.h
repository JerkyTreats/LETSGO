﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "MetaSoundPlayerData.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct LETSGO_API FMetaSoundPlayerData
{
	GENERATED_BODY()
	
public:
	FMetaSoundPlayerData();
	explicit FMetaSoundPlayerData(USoundWave* Cue);
	FMetaSoundPlayerData(USoundWave* Cue, const float Volume);
	~FMetaSoundPlayerData();

	UPROPERTY(BlueprintReadOnly, Category="LETSGO")
	FName WaveAssetName = FName(TEXT("WaveAsset"));

	UPROPERTY(BlueprintReadOnly, Category="LETSGO")
	FName OutputVolumeName = FName(TEXT("OutputVolume"));

	UPROPERTY(BlueprintReadOnly, Category="LETSGO")
	USoundWave* WaveAsset;

	UPROPERTY(BlueprintReadOnly, Category="LETSGO")
	float OutputVolume = 1.0f;
};
