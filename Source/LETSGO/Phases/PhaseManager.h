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
class LETSGO_API UPhaseManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	// 

public:
	UPhaseManager();
	
	UPROPERTY()
	TArray<IPhaseController*> Phases;
	
	bool TickEnabled = false;
	


private:
	// The last frame number we were ticked.
	// We don't want to tick multiple times per frame 
	uint32 LastFrameNumberWeTicked = INDEX_NONE;

	int EmptyListWarnAmount = 0;

public:
	UFUNCTION()
	void Initialize();
	
	UFUNCTION()
	void ProcessPhases();
	
	// FTickableGameObject Begin
	virtual bool IsTickable() const override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Conditional;
	}
	
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UPhaseManager, STATGROUP_Tickables);
	}
	
	virtual bool IsTickableWhenPaused() const override
	{
		return true;
	}
	
	virtual bool IsTickableInEditor() const override
	{
		return false;
	}
	// FTickableGameObject End
};
