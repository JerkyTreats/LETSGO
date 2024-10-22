// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicComposerState.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/Instrument.h"
#include "MusicConductor.generated.h"

USTRUCT()
struct FMusicConductorData
{
	GENERATED_BODY()

	UPROPERTY()
	int ComposerDataIndex;
	//TSharedPtr<FComposerData> ComposerData;

	UPROPERTY()
	AInstrument* Instrument;
};

UCLASS()
class LETSGO_API AMusicConductor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMusicConductor();

	UPROPERTY()
	AMusicComposerState* ComposerState;

	UPROPERTY()
	TArray<FMusicConductorData> ConductorDatas;

	UPROPERTY()
	UQuartzClockHandle* Clock;

	UPROPERTY()
	FOnQuartzMetronomeEventBP QuantizationDelegate;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AInstrument> InstrumentClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	void SetClock();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();
	
	UFUNCTION()
	void OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};
