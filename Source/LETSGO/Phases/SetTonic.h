// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "LETSGO/AudioPlatform//AAudioPlatform.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "UObject/Object.h"
#include "SetTonic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhaseControllerCompletedDelegate, TScriptInterface<IPhaseController>, PhaseController);

/**
 * 
 */
UCLASS()
class LETSGO_API ASetTonic : public AActor, public IPhaseController
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
	ASetTonic();

	UPROPERTY(BlueprintReadWrite, Category="LETSGO | Audio Platform Spawner")
	float OffsetAmountPerSpawnedPlatform = 150.0f;

	UPROPERTY()
	int NumPlatformsToSpawn = 3;
	
	UPROPERTY()
	TArray<AAudioPlatform*> AudioPlatforms;
	
	UPROPERTY()
	AAudioPlatformSpawner* Spawner;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO | Audio Platform Spawner")
	TSubclassOf<AAudioPlatformSpawner> AudioPlatformSpawnerClass;
	
	UPROPERTY()
	FPhaseControllerCompletedDelegate OnPhaseComplete;
	
protected:
	bool Active = false;
	bool Completed = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	
public:
	// Function to fire when the OnAudioPlatformTriggered Event is received
	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote) ;

	UFUNCTION()
	void SetTonic(FLetsGoMusicNotes Note);

	UFUNCTION()
	void Initialize();

	// Interface Methods
	UFUNCTION()
	virtual void Activate() override;

	UFUNCTION()
	virtual bool IsActivated() override;
	
	UFUNCTION()
	virtual void Deactivate() override;

	UFUNCTION()
	virtual void Complete() override;

	UFUNCTION()
	virtual bool IsCompleted() override;

	UFUNCTION()
	static FLetsGoMusicNotes GetRandomNote();

	UFUNCTION()
	int DivRoundClosest(const int n, const int d);
};
