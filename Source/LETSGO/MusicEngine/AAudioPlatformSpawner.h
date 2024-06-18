// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAudioPlatform.h"
#include "UNoteContainer.h"
#include "GameFramework/Actor.h"
#include "AAudioPlatformSpawner.generated.h"

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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FTransform GetCameraVectorForward() const;

	UFUNCTION()
	AAudioPlatform* SpawnPlatform(const FTransform& SpawnLocation, FLetsGoMusicNotes Note);
};
