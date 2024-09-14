// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "GameFramework/Actor.h"
#include "Sleep.generated.h"

UCLASS()
class LETSGO_API ASleep : public AActor, public IPhaseController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASleep();

	float SleepTime = 2.0f;
	
protected:
	bool Active = false;
	bool Completed = false;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize(float SleepAmount);
	
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
};
