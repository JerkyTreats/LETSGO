// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "MetasoundSource.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/MusicEngine/ClockSettings.h"
#include "Instrument.generated.h"

// See https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
UCLASS()
class LETSGO_API AInstrument : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInstrument();

	UPROPERTY()
	AClockSettings* ClockSettings;
	
	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	UQuartzClockHandle* Clock;
	
	/**
	 * Quantization Metronome Event Delegate
	 * This is bound to OnQuantizationBoundaryTriggered in ctor
	 */
	UPROPERTY()
	FOnQuartzMetronomeEventBP PlayQuantizationDelegate;

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	FQuartzQuantizationBoundary QuartzQuantizationBoundary = {
		EQuartzCommandQuantization::Bar,
		1.0f,
		EQuarztQuantizationReference::BarRelative,
		true
	};

	UPROPERTY()
	FInstrumentSchedule InstrumentSchedule;

	UPROPERTY()
	int CurrentBar = 0;

	UPROPERTY()
	EQuartzCommandQuantization RelativeQuantizationResolution;

	UPROPERTY()
	EQuarztQuantizationReference RelativeQuantizationReference = EQuarztQuantizationReference::BarRelative;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetClock();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize(const FInstrumentSchedule& Schedule);
	
	UFUNCTION()
	void StartPlaying();

	UFUNCTION()
	void StopPlaying();
	
	/**
	 * Function intended to trigger on Clock Quantization Subscription event
	 * ie. Fire this function on every Beat
	 * The params are not necessarily used, are defined from the Clock Quantization event delegate
	 * @param DrumClockName Clock name for this instrument
	 * @param QuantizationType Bar, beat, half step, etc
	 * @param NumBars ?
	 * @param Beat ?
	 * @param BeatFraction ? 
	 */
	UFUNCTION()
	void OnQuantizationBoundaryTriggered(FName DrumClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
	
};
