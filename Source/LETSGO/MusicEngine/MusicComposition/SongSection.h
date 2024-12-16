// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicStrategy.h"
#include "UObject/Object.h"
#include "SongSection.generated.h"

UENUM()
enum ESongSection
{
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

	FSectionStrategy(IMusicStrategy* InStrategy, float Appropriateness);
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

	TArray<FSectionStrategy> MusicStrategies;

	FSongSection(ESongSection InType, TArray<FSectionStrategy> InStrategies)
	{
		Type = InType;
		MusicStrategies = InStrategies;
	}
};

USTRUCT()
struct FSongSections
{
	GENERATED_BODY()

	TArray<FSongSection> SongSections;

	static FSongSections InitializeSongSections();
};
