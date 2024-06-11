// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "LETSGO/MusicEngine/AAudioPlatform.h"
#include "UObject/Object.h"
#include "SetTonic.generated.h"

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
	UPROPERTY()
	TArray<AAudioPlatform*> AudioPlatforms;
	

	
protected:
	bool Active = false;

public:
	// Function to fire when the OnAudioPlatformTriggered Event is received
	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote);

	UFUNCTION()
	void SetTonic(FLetsGoMusicNotes Note);

	UFUNCTION()
	virtual void Initialize() override;
	
	UFUNCTION()
	virtual void Activate() override;
	
	UFUNCTION()
	virtual void Deactivate() override;
};
