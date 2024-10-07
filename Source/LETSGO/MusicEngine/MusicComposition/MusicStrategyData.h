// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicStrategy.h"
#include "MusicStrategyData.generated.h"

UENUM()
enum EMusicStrategies
{
	PedalPoint,
	CreateMotif,
};


USTRUCT()
struct FMusicStrategyData
{
	GENERATED_BODY()

	IMusicStrategy* Strategy;
	TEnumAsByte<EMusicStrategies> StrategyType;

	float StrategyAppropriateness = 0.0f;

	TArray<FInstrumentInputData> InstrumentInputs;


	FMusicStrategyData();
	FMusicStrategyData(IMusicStrategy* InputStrategy, float Appropriateness);

	void GenerateInstrumentInputs(const TArray<FComposerData> ComposerDataSet);
};