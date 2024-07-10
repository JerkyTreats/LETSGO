﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "PhaseManager.h"
#include "LETSGO/AudioPlatform//AAudioPlatform.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "UObject/Object.h"
#include "SetTonic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhaseControllerDeactivateDelegate, IPhaseController*, PhaseController);

/**
 * 
 */
UCLASS()
class LETSGO_API USetTonic : public UObject, public IPhaseController
{
	GENERATED_BODY()

	/*
	 *	AudioPlatform Broadcasts OnAudioPlatformTriggered
	 *	SetTonic Phase has references to three AudioPlatforms
	 *	On Activate method, SetTonic spawns the three AudioPlatforms in front of the Player
	 *		-> Binds to all OnAudioPlatformTriggered events
	 *	When OnAudioPlatformTriggered event received:
	 *		-> Destroy all Platform
	 *		-> Set Tonic in GameState
	 */


public:
	USetTonic();

	UPROPERTY()
	float OffsetAmountPerSpawnedPlatform = 40;

	UPROPERTY()
	int NumPlatformsToSpawn = 3;
	
	UPROPERTY()
	TArray<AAudioPlatform*> AudioPlatforms;
	
	UPROPERTY()
	AAudioPlatformSpawner* Spawner;
	
	UPROPERTY()
	FPhaseControllerActivateDelegate OnPhaseDeactivate;
	
protected:
	bool Active = false;

public:
	// Function to fire when the OnAudioPlatformTriggered Event is received
	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote) ;

	UFUNCTION()
	void SetTonic(FLetsGoMusicNotes Note);

	UFUNCTION()
	virtual void Initialize(UPhaseManager* PhaseManager) override;

	UFUNCTION()
	static FLetsGoMusicNotes GetRandomNote();
	
	UFUNCTION()
	virtual void Activate() override;
	
	UFUNCTION()
	virtual void Deactivate() override;
};
