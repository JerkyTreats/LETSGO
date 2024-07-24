// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LETSGO/Phases/PhaseManager.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "ALetsGoGameMode.generated.h"

/**
 * Custom Game Mode for LETSGO.
 *
 * This acts as a Controller in a MVC software design pattern
 * It is intended to facilitate inter-asset communication
 * 
 */
UCLASS()
class LETSGO_API ALetsGoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO | Audio Platform Spawner")
	TSubclassOf<APhaseManager> PhaseManagerClass;

	UPROPERTY()
	APhaseManager* PhaseManager;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	ALetsGoGameMode();
	
	UFUNCTION(BlueprintCallable, Category="LETSGO | Music Theory")
	void SetTonic(FLetsGoMusicNotes Note) const; 

	UFUNCTION(BlueprintPure, Category="LETSGO | Clock")
	UQuartzClockHandle* GetMainClock() const;
	
	UFUNCTION(BlueprintCallable, Category="LETSGO | Clock")
	virtual void SetMainClock(UQuartzClockHandle* Clock);

	UFUNCTION()
	void InitializeGameplay();
};
