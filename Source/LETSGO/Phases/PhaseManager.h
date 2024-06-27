// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "UObject/Object.h"
#include "PhaseManager.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API UPhaseManager : public UObject
{
	GENERATED_BODY()

	// 

public:
	UPhaseManager();
	
	UPROPERTY()
	TArray<IPhaseController*> Phases;


	
};
