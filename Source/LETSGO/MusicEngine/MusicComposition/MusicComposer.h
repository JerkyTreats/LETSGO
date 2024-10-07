// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComposerData.h"
#include "MusicStrategy.h"
#include "MusicStrategyData.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/Instruments/Drum/DrumSoundCueMapping.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "MusicComposer.generated.h"



UCLASS()
class LETSGO_API AMusicComposer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMusicComposer();

	UPROPERTY()
	int32 BarCreationThreshold = 4;
	
	UPROPERTY()
	FLetsGoGeneratedScale Scale; 

	UPROPERTY()
	TArray<FComposerData> ComposerDataObjects;

	UPROPERTY()
	TArray<FMusicStrategyData> MusicalStrategies;
	
	UPROPERTY()
	FOnQuartzMetronomeEventBP OnBeatQuantizationDelegate;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<ADrumSoundCueMapping> ADrumSoundCueMappingClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void InitializeComposerData();
	
	UFUNCTION()
	void InitializeStrategies();

	UFUNCTION()
	FInstrumentScheduleData GenerateBars(FComposerData ComposerData, int StartAtBar, int TimesToRepeat);

	UFUNCTION()
	void GenerateScale();

	UFUNCTION()
	void OnBeat(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};
