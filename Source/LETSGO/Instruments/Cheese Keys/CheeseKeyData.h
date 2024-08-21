// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
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
	UMetaSoundSource* Sound;

	FCheeseKeyData();

	FCheeseKeyData(int SetOctave, ELetsGoMusicNotes SetNote, UMetaSoundSource* SetSound);
	
	UFUNCTION()
	static TArray<FCheeseKeyData> GenerateKeys(TArray<UMetaSoundSource*> Sounds);
};
