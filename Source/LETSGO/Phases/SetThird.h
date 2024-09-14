// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "GameFramework/Actor.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "SetThird.generated.h"

UCLASS()
class LETSGO_API ASetThird : public AActor, public IPhaseController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASetThird();

	UPROPERTY()
	FLetsGoMusicNotes Tonic;

	UPROPERTY()
	AAudioPlatformSpawner* Spawner;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AAudioPlatformSpawner> AudioPlatformSpawnerClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Completed = false;
	bool Active = false;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// IPhase Controller 
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
	virtual void InitiateDestroy() override;
	// End IPhaseController

	UFUNCTION()
	void Initialize();
	
	UFUNCTION()
	void SetTonic();
	
	UFUNCTION()
	void SetThird(FLetsGoMusicNotes Note);
};
