// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "UObject/Interface.h"
#include "MusicStrategy.generated.h"

class AMusicComposerState;
struct FInstrumentScheduleData;
struct FLetsGoGeneratedScale;
struct FComposerData;

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
	virtual FPerBarSchedule GenerateBar(const FComposerData& CurrentComposerData, const AMusicComposerState* State) = 0;

	virtual float GetStrategyAppropriateness(const FComposerData& CurrentComposerData, const AMusicComposerState* State) = 0;

	virtual float GetInstrumentAppropriateness(const FComposerData& CurrentComposerData, const AMusicComposerState* State) = 0;
};
