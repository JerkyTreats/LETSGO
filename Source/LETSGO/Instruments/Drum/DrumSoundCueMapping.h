﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentNote.h"
#include "LETSGO/MusicEngine/MusicComposition/ComposerData.h"
#include "DrumSoundCueMapping.generated.h"

UCLASS()
class LETSGO_API ADrumSoundCueMapping : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrumSoundCueMapping();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	USoundWave* Kick;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	USoundWave* Snare;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	USoundWave* HiHatOpen;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	USoundWave* HiHatClosed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	USoundWave* Clap;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	static FInstrumentData GenerateInstrumentData(USoundWave* Sound);

	UFUNCTION()
	FInstrumentData GetInstrumentData(EInstrumentRoles InstrumentRole) const;
};
