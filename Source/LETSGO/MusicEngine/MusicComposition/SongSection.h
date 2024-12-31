// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComposerData.h"
#include "MusicStrategy.h"
#include "Strategy_CreateMotif.h"
#include "Strategy_PedalPointComposition.h"
#include "UObject/Object.h"
#include "SongSection.generated.h"

UENUM()
enum ESongSection
{
	Null,
	Intro,
	Episode,
	Refrain,
	Bridge,
	Outro,
};

USTRUCT()
struct FSectionStrategy
{
	GENERATED_BODY()

	IMusicStrategy* MusicStrategy;

	float Appropriateness;

	FSectionStrategy(): MusicStrategy(nullptr), Appropriateness(0)
	{
	}

	FSectionStrategy(IMusicStrategy* InStrategy, float InAppropriateness)
	{
		MusicStrategy = InStrategy;
		Appropriateness = InAppropriateness;
	}
};

USTRUCT()
struct FSectionInstrumentPlan
{
	GENERATED_BODY()

	UPROPERTY()
	TEnumAsByte<EInstrumentRoles> InstrumentRole = None;

	UPROPERTY()
	int StartAtBar = -1;

	UPROPERTY()
	int EndAtBar = -1; 

	UPROPERTY()
	TScriptInterface<IMusicStrategy> MusicStrategy;
};

/**
 * 
 */
USTRUCT()
struct FSongSection 
{
	GENERATED_BODY()

	UPROPERTY()
	TEnumAsByte<ESongSection> Type;

	UPROPERTY()
	TArray<FSectionInstrumentPlan> GeneratedPlans;

	UPROPERTY()
	TArray<FSectionStrategy> CandidateStrategies;

	FSongSection(): Type(Null) {}

	FSongSection(ESongSection InType)
	{
		Type = InType;
	}

	void GenerateInstrumentPlans(TArray<TEnumAsByte<EInstrumentRoles>> InstrumentRoles);
};

USTRUCT()
struct FSongSections
{
	GENERATED_BODY()

	IMusicStrategy* PedalPoint;
	IMusicStrategy* CreateMotif;

	UPROPERTY()
	int DesiredSectionsAmount = 0;

	UPROPERTY()
	TArray<TEnumAsByte<EInstrumentRoles>> InstrumentRoles;

	UPROPERTY()
	TArray<FSongSection> CandidateSections;

	UPROPERTY()
	TArray<FSongSection> GeneratedSections;

	FSongSections()
	{
		PedalPoint = NewObject<UStrategy_PedalPointComposition>();
		CreateMotif = NewObject<UStrategy_CreateMotif>();
	};

	void InitializeSongSections();

	void GenerateSongSections();

	void GenerateNextSongSection();
};
