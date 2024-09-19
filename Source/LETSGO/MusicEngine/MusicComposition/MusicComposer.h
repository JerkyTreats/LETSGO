// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicCompositionStrategy.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "MusicComposer.generated.h"

USTRUCT()
struct FComposerData
{
	GENERATED_BODY()

	int NumBarsToCompose;
	FLetsGoGeneratedScale Scale;
	int OctaveMin = 1;
	int OctaveMax = 5;
	FInstrumentSchedule InstrumentScheduleInput;
};


USTRUCT()
struct FMusicStrategyData
{
	GENERATED_BODY()

	IMusicCompositionStrategy* Strategy;
	// type = PedalPoint; CreateMotif
	// requirements = [ SetTonic, SetThird, Motif ] 
};

UCLASS()
class LETSGO_API AMusicComposer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMusicComposer();

	UPROPERTY()
	FComposerData ComposerData;

	UPROPERTY()
	FLetsGoGeneratedScale Scale; 

	UPROPERTY()
	TArray<IMusicCompositionStrategy*> CompositionStrategies;

	UPROPERTY()
	TArray<FInstrumentSchedule> CreatedSchedules;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void GenerateScale();

	UFUNCTION()
	void SetComposerData(FComposerData NewDataObject);

	UFUNCTION()
	void ChooseMusicalStrategy();

	UFUNCTION()
	FInstrumentSchedule ComposeInstrumentSchedule();
};
