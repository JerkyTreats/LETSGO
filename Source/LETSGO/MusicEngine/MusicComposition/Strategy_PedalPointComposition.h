﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicComposerState.h"
#include "MusicStrategy.h"
#include "UObject/Object.h"
#include "Strategy_PedalPointComposition.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UStrategy_PedalPointComposition : public UObject, public IMusicStrategy
{
	GENERATED_BODY()

public:
	virtual FPerBarSchedule GenerateBar(TSharedPtr<FComposerData> CurrentComposerData, const AMusicComposerState* State) override;
	virtual float GetStrategyAppropriateness(TSharedPtr<FComposerData> CurrentComposerData, const AMusicComposerState* State) override;
	virtual float
	GetInstrumentAppropriateness(TSharedPtr<FComposerData> CurrentComposerData, const AMusicComposerState* State) override;
};
