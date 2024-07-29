﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "MetasoundSource.h"
#include "Drums.generated.h"

// See https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
UCLASS()
class LETSGO_API ADrums : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrums();

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	UQuartzClockHandle* Clock;

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	UAudioComponent* InstrumentAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LETSGO")
	UMetaSoundSource* InstrumentMetaSoundSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LETSGO")
	EQuartzCommandQuantization InQuantizationBoundary = EQuartzCommandQuantization::EighthNote;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LETSGO")
	FQuartzQuantizationBoundary QuartzQuantizationBoundary = {
		InQuantizationBoundary,
		1.0f,
		EQuarztQuantizationReference::BarRelative,
		true
	};

	/** Used to bind the FPlayQuantizedDelegate in the class constructor. */
	FOnQuartzCommandEventBP PlayQuantizationDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LETSGO")
	FName ClockName = "DrumsClock";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LETSGO")
	float BPM = 120.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	* @brief Function delegate. Triggers its functionality synced with the clock.
	* @param EventType Use a switch on this enumeration to select "CommandOnQueued". 
	* @param Name 
	*/
	UFUNCTION()
	void FPlayQuantizedDelegate(EQuartzCommandDelegateSubType EventType, FName Name);
};