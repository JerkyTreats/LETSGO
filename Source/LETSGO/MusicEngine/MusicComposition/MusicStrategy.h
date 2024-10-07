// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComposerData.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "UObject/Interface.h"
#include "MusicStrategy.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMusicStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LETSGO_API IMusicStrategy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FInstrumentSchedule Apply(FComposerData& Data) = 0;

	virtual float GetStrategyAppropriateness(FComposerData CurrentComposerData, TArray<FComposerData> ComposerDataSet, FLetsGoGeneratedScale Scale) = 0;

	virtual float GetInstrumentAppropriateness(FComposerData CurrentComposerData, TArray<FComposerData> ComposerDataSet) = 0;
};
