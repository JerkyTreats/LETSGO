// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALetsGoGameState.h"
#include "GameFramework/GameModeBase.h"
#include "LETSGO/Instruments/InstrumentRack.h"
#include "LETSGO/MusicEngine/ClockSettings.h"
#include "LETSGO/Phases/PhaseManager.h"
#include "ALetsGoGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMusicalStateUpdateDelegate);

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

	UPROPERTY()
	FMusicalStateUpdateDelegate OnMusicalStateUpdated;

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

	// Second
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetSecond(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetSecond() const; 
	
	// Third
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetThird(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetThird() const;

	// Fourth
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetFourth(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetFourth() const; 

	// Fifth
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetFifth(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetFifth() const;

	// Sixth
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetSixth(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetSixth() const;

	// Seventh
	UFUNCTION(BlueprintCallable, Category="LETSGO")
	void SetSeventh(FLetsGoMusicNotes Note) const;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	FLetsGoMusicNotes GetSeventh() const; 



	
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
