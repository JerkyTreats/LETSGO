// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
#include "InstrumentSchedule.generated.h"


USTRUCT()
struct FNotesPerBar
{
	GENERATED_BODY()

	UPROPERTY()
	float Beat;

	UPROPERTY()
	UMetaSoundSource* SoundCue;

	FNotesPerBar(): Beat(0), SoundCue(nullptr){}

	explicit FNotesPerBar(const float BeatNum, UMetaSoundSource* Cue): Beat(BeatNum), SoundCue(Cue) {}
	explicit FNotesPerBar(const float BeatNum): Beat(BeatNum), SoundCue(nullptr) {}
};

USTRUCT()
struct FPerBarSchedule
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FNotesPerBar> NotesInBar; // [ { 1, CSharp1 }, { 3, CSharp2 }
	
	FPerBarSchedule() {}
	explicit FPerBarSchedule(UMetaSoundSource* SoundCue, const TArray<float>& Beats);
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
