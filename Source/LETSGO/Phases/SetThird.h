// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "GameFramework/Actor.h"
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

	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	virtual bool IsActivated() override;
	virtual void Deactivate() override;
	virtual void Complete() override;
	virtual bool IsCompleted() override;
	virtual void InitiateDestroy() override;
};
