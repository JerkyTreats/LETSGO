// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicCompositionStrategy.h"
#include "UObject/Object.h"
#include "Strategy_PedalPointComposition.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UStrategy_PedalPointComposition : public UObject, public IMusicCompositionStrategy
{
	GENERATED_BODY()

public:
	virtual FInstrumentSchedule Apply(FComposerData& Data) override;
};
