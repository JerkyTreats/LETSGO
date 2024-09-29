// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComposerData.h"
#include "MusicCompositionStrategy.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
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
	FLetsGoGeneratedScale Scale; 

	UPROPERTY()
	TArray<FComposerData> ComposerDataObjects;

	UPROPERTY()
	TArray<FMusicalStrategy> MusicalStrategies;
	
	UPROPERTY()
	FOnQuartzMetronomeEventBP OnBeatQuantizationDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void InitializeStrategies();

	UFUNCTION()
	void GenerateScale();

	UFUNCTION()
	void AddComposerData(FComposerData NewDataObject);
	
	UFUNCTION()
	void MergeComposerData(FComposerData NewDataObject);

	UFUNCTION()
	void ChooseMusicalStrategy();

	UFUNCTION()
	FInstrumentSchedule ComposeInstrumentSchedule();

	UFUNCTION()
	void OnBeat(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};
