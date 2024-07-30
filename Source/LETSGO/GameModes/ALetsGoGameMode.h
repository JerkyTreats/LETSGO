// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LETSGO/Instruments/InstrumentRack.h"
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

	// Tonic
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetTonic(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetTonic() const; 
	

	// Clock
	UFUNCTION(BlueprintPure, Category="LETSGO")
	UQuartzClockHandle* GetMainClock() const;
	
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	virtual void SetMainClock(UQuartzClockHandle* Clock);

	// Instrument Rack
	UFUNCTION()
	void SetInstrumentRack(UInstrumentRack* Rack);

	UFUNCTION()
	UInstrumentRack* GetInstrumentRack();

	UFUNCTION()
	void InitializeGameplay();
};
