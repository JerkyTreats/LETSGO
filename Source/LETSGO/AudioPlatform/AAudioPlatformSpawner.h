// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAudioPlatform.h"
#include "LETSGO/MusicEngine/UNoteContainer.h"
#include "GameFramework/Actor.h"
#include "AAudioPlatformSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnerNoteTriggeredDelegate, FLetsGoMusicNotes, Note);


UCLASS()
class LETSGO_API AAudioPlatformSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAudioPlatformSpawner();

	UPROPERTY(Blueprintable)
	TArray<AAudioPlatform*> SpawnedPlatforms;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	UNoteContainer* NoteContainer;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	FVector CameraVectorForwardOffsetAmount { 500.0f, 500.0f, 0 };
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "LETSGO | AudioPlatformSpawner")
	TSubclassOf<AAudioPlatform> AAudioPlatformClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO | AudioPlatformSpawner")
	float DestroyDelay = 0.4f;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO | AudioPlatformSpawner")
	FSpawnerNoteTriggeredDelegate OnAudioPlatformTriggered;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UWorld* World;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FTransform GetCameraVectorForward() const;

	UFUNCTION()
	AAudioPlatform* SpawnPlatform(const FTransform& SpawnLocation, const FLetsGoMusicNotes Note);

	UFUNCTION()
	void InitiateDestroy();
	
	UFUNCTION()
	void DestroyActor();

	
};
