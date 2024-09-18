// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Instrument.h"
#include "Drum/DrumData.h"
#include "Drum/DrumSoundCueMapping.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentRack.h"
#include "LETSGO/Phases/PhaseController.h"
#include "StartDrums.generated.h"

UCLASS()
class LETSGO_API AStartDrums : public AActor, public IPhaseController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStartDrums();

	UPROPERTY()
	bool IsActive;

	UPROPERTY()
	bool IsComplete;

	UPROPERTY()
	AInstrument* Kick; 

	UPROPERTY()
	AInstrument* Snare;

	UPROPERTY()
	AInstrument* HiHatOpen;

	UPROPERTY()
	AInstrument* HiHatClosed;

	UPROPERTY()
	AInstrument* Clap;

	UPROPERTY()
	UInstrumentRack* InstrumentRack;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<ADrumSoundCueMapping> ADrumSoundCueMappingClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AInstrument> InstrumentClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	EDrumPatterns GetRandomDrumPattern();

	FDrumPattern GetDrumData(EDrumPatterns Pattern);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize();

	virtual void Activate() override;
	virtual bool IsActivated() override;
	
	virtual void Deactivate() override;
	
	virtual void Complete() override;
	virtual bool IsCompleted() override;

	virtual void InitiateDestroy() override;
};
