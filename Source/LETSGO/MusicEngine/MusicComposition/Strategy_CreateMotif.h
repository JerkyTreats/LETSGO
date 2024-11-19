// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicStrategy.h"
#include "UObject/Object.h"
#include "Strategy_CreateMotif.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UStrategy_CreateMotif : public UObject, public IMusicStrategy
{
	GENERATED_BODY()

public:
	virtual FPerBarSchedule
	GenerateBar(FComposerData& CurrentComposerData, const AMusicComposerState* State) override;
	virtual float
	GetStrategyAppropriateness(FComposerData& CurrentComposerData, const AMusicComposerState* State) override;
	virtual float GetInstrumentAppropriateness(FComposerData& CurrentComposerData,
		const AMusicComposerState* State) override;
};
