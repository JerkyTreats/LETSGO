// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InstrumentRack.generated.h"

/**
 * Acts as a Container for Instruments to be stored in State
 * Required for Start/Stop instrument phases who don't share references to the Instruments they manage
 */
UCLASS()
class LETSGO_API UInstrumentRack : public UObject
{
	GENERATED_BODY()

public:
	UInstrumentRack();
	
	UPROPERTY()
	TArray<AActor*> Instruments;

	UFUNCTION()
	void AddInstrument(AActor* Instrument);
};
