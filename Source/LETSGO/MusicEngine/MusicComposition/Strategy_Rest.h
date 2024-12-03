// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicComposerState.h"
#include "MusicStrategy.h"
#include "UObject/Object.h"
#include "Strategy_Rest.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UStrategy_Rest : public UObject, public IMusicStrategy
{
	GENERATED_BODY()

public:
	virtual FInstrumentSchedule GenerateInstrumentSchedule(FComposerData& CurrentComposerData, const AMusicComposerState* State, const int StartAtBar) override;
	virtual float GetStrategyAppropriateness(FComposerData& CurrentComposerData, const AMusicComposerState* State) override;
	virtual float
	GetInstrumentAppropriateness(FComposerData& CurrentComposerData, const AMusicComposerState* State) override;
};
