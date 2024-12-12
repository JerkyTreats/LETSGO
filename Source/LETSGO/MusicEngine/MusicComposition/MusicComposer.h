// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComposerData.h"
#include "MusicComposerState.h"
#include "MusicStrategy.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/Instrument.h"
#include "MusicComposer.generated.h"

UCLASS()
class LETSGO_API AMusicComposer : public AActor
{
	GENERATED_BODY()

public:
	AMusicComposer();

	UPROPERTY()
	AMusicComposerState* ComposerState;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AMusicComposerState> ComposerStateClass;

	UPROPERTY()
	TArray<IMusicStrategy*> MusicalStrategies;
	
	UPROPERTY()
	FOnQuartzMetronomeEventBP OnBeatQuantizationDelegate;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AInstrument> InstrumentClass;

	UPROPERTY()
	TArray<int> MusicalIdeaSeed;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	bool Started = false;

	int LastProcessedBar = 0;

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
	void GenerateMusicalIdea();
	
	IMusicStrategy* ChooseMusicalStrategy(FComposerData& ComposerData, float& AppropriatenessOut);
	
	UFUNCTION()
	void GenerateScale();

	UFUNCTION()
	void UpdateAllowableNoteIndices(int Interval);

	// FInstrumentSchedule GenerateBars(FComposerData Data);

};
