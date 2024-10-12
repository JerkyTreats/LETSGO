// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	virtual FInstrumentSchedule Apply(FComposerData& ComposerData, FInstrumentScheduleData InstrumentScheduleData) override;
	virtual float GetStrategyAppropriateness(FComposerData CurrentComposerData, TArray<FComposerData> ComposerDataSet, FLetsGoGeneratedScale Scale) override;
	virtual float
	GetInstrumentAppropriateness(FComposerData CurrentComposerData, TArray<FComposerData> ComposerDataSet) override;
};
