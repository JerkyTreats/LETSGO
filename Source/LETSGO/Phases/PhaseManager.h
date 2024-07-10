// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "UObject/Object.h"
#include "PhaseManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhaseControllerActivateDelegate, IPhaseController*, PhaseController);


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

	UPROPERTY()
	FPhaseControllerActivateDelegate OnPhaseActivate;

	UFUNCTION()
	void Initialize();
	
	UFUNCTION()
	void ProcessPhases();

	UFUNCTION()
	void ActivatePhase(IPhaseController* ToActivate);
	
	UFUNCTION()
	void DeactivatePhase(IPhaseController* ToDeactivate);

	UFUNCTION()
	void RemovePhase(IPhaseController* ToRemove);
};
