// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "SetTonic.h"
#include "StartClock.h"
#include "LETSGO/Instruments/StartInstrument.h"
#include "UObject/Object.h"
#include "PhaseManager.generated.h"


/**
 * 
 */
UCLASS()
class LETSGO_API APhaseManager : public AActor//, public FTickableGameObject
{
	GENERATED_BODY()

	// 

public:
	APhaseManager();
	
	UPROPERTY()
	TArray<IPhaseController*> Phases;
	
	UPROPERTY()
	bool TickEnabled = false;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<ASetTonic> SetTonicClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AStartInstrument> StartInstrumentClass; 

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AStartClock> StartClockClass;

private:
	// The last frame number we were ticked.
	// We don't want to tick multiple times per frame 
	uint32 LastFrameNumberWeTicked = INDEX_NONE;

	int EmptyListWarnAmount = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:
	UFUNCTION()
	void Initialize();
	
	UFUNCTION()
	void ProcessPhases();
	
	virtual void Tick(float DeltaTime) override;
	
};
