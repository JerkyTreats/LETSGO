// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicCompositionStrategy.h"
#include "UObject/Object.h"
#include "PedalPoint_MusicalStrategy.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UPedalPoint_MusicalStrategy : public UObject, public IMusicCompositionStrategy
{
	GENERATED_BODY()

public:
	virtual FInstrumentSchedule Apply(const FComposerData& Data) override;
};
