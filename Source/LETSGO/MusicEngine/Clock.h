﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Phases/PhaseController.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Clock.generated.h"

// See https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
UCLASS()
class LETSGO_API AClock : public AActor, public IPhaseController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AClock();

	UPROPERTY(BlueprintReadWrite)
	UQuartzClockHandle* Clock;

	UPROPERTY(BlueprintReadWrite)
	FName ClockName;

	// Defaults to quarter note, this is public so should be able to override as necessary
	UPROPERTY(BlueprintReadWrite)
	FQuartzTimeSignature TimeSignature = {};

	// 120 is Ableton's default so why not here?
	UPROPERTY(BlueprintReadWrite)
	float BeatsPerMinute = 120.0f;

	UPROPERTY()
	bool IsActive = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void Initialize();

	virtual void Activate() override ;
	virtual bool IsActivated() override;
	
	virtual void Deactivate() override;
	
	virtual void Complete() override;
	virtual bool IsCompleted() override;
};
