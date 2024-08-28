// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/Instruments/MetaSoundPlayerData.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "CheeseKeyData.generated.h"

/**
 * 
 */
USTRUCT()
struct FCheeseKeyData {
	GENERATED_BODY()

	UPROPERTY()
	int Octave; 
	
	UPROPERTY()
	TEnumAsByte<ELetsGoMusicNotes> Note;

	UPROPERTY()
	FMetaSoundPlayerData SoundData;

	FCheeseKeyData();

	FCheeseKeyData(int SetOctave, ELetsGoMusicNotes SetNote, const FMetaSoundPlayerData& SetData);
	
	static TArray<FCheeseKeyData> GenerateKeys(TArray<USoundWave*> Sounds);
};
