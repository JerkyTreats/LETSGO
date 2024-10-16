// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALetsGoGameState.h"
#include "GameFramework/GameModeBase.h"
#include "LETSGO/Instruments/InstrumentRack.h"
#include "LETSGO/MusicEngine/ClockSettings.h"
#include "LETSGO/Phases/PhaseManager.h"
#include "ALetsGoGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTonicSet);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIntervalSet, int, Interval);

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
	UPROPERTY()
	ALetsGoGameState* State;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO | Audio Platform Spawner")
	TSubclassOf<APhaseManager> PhaseManagerClass;

	UPROPERTY()
	APhaseManager* PhaseManager;

	UPROPERTY()
	FTonicSet OnTonicSet;

	UPROPERTY()
	FIntervalSet OnIntervalSet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	ALetsGoGameMode();


	// MUSICAL STATE
	// Tonic
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetTonic(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetTonic() const; 
	
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoGeneratedScale GetChromaticScale() const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetInterval(int Interval) const;

	
	
	// Clock
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	AClockSettings* GetClockSettings() const;
	
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	virtual void SetClockSettings(AClockSettings* Clock);

	// Instrument Rack
	UFUNCTION()
	void SetInstrumentRack(UInstrumentRack* Rack);

	UFUNCTION()
	UInstrumentRack* GetInstrumentRack();

	
	// Instrument Data
	UFUNCTION()
	void SetInstrumentData_CheeseKey(ACheeseKeySoundCueMapping* DataToSet);

	UFUNCTION()
	ACheeseKeySoundCueMapping* GetInstrumentData_CheeseKey();

	UFUNCTION()
	void SetInstrumentData_Drums(ADrumSoundCueMapping* DataToSet);

	UFUNCTION()
	ADrumSoundCueMapping* GetInstrumentData_Drums();

	
	// Music Composer
	AMusicComposer* GetMusicComposer();

	void SetMusicComposer(AMusicComposer* Composer);
	
	UFUNCTION()
	void InitializeGameplay();
};
