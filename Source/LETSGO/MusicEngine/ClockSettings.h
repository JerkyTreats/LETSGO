// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "ClockSettings.generated.h"

UCLASS()
class LETSGO_API AClockSettings : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AClockSettings();
	
	// Defaults to quarter note, this is public so should be able to override as necessary
	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	FQuartzTimeSignature TimeSignature = {};

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	FQuartzClockSettings ClockSettings;
	
	// 120 is Ableton's default so why not here?
	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	float BeatsPerMinute = 120.0f;

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	FQuartzQuantizationBoundary QuartzQuantizationBoundary = {
		EQuartzCommandQuantization::Bar,
		1.0f,
		EQuarztQuantizationReference::BarRelative,
		true
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="LETSGO")
	UQuartzClockHandle* GetNewClock(FName ClockIdentifier) const;
};
