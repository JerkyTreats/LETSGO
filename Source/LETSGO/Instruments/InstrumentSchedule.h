// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaSoundPlayerData.h"
#include "MetasoundSource.h"
#include "InstrumentSchedule.generated.h"


USTRUCT()
struct FNotesPerBar
{
	GENERATED_BODY()

	UPROPERTY()
	float Beat;

	UPROPERTY()
	FMetaSoundPlayerData SoundData;

	FNotesPerBar(): Beat(0) {}

	explicit FNotesPerBar(const float BeatNum, USoundWave* Sound): Beat(BeatNum), SoundData(FMetaSoundPlayerData(Sound)) {}
	explicit FNotesPerBar(const float BeatNum, const FMetaSoundPlayerData& Data): Beat(BeatNum), SoundData(Data) {}
};

USTRUCT()
struct FPerBarSchedule
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FNotesPerBar> NotesInBar; // [ { 1, [ Note: CSharp1, Vol: 0.5 ] } ... ]
	
	FPerBarSchedule() {}
	explicit FPerBarSchedule(USoundWave* SoundCue, TArray<float> Beats);
	explicit FPerBarSchedule(const TArray<FNotesPerBar>& Notes) : NotesInBar(Notes) {}
};

USTRUCT()
struct FInstrumentSchedule
{
	GENERATED_BODY()
	
	UPROPERTY()
	EQuartzCommandQuantization QuantizationDivision;
	
	UPROPERTY()
	TArray<FPerBarSchedule> BeatSchedule; // [[1,3],[1,3],[1,3],[1,2,3,4]] play 1-3, on 4th bar 4onfloor

	FInstrumentSchedule(): QuantizationDivision() {} ;
	explicit FInstrumentSchedule(const EQuartzCommandQuantization Quantization, const TArray<FPerBarSchedule>& Pattern);

};
