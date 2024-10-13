// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComposerData.h"
#include "MusicComposerState.h"
#include "GameFramework/Actor.h"
#include "MusicComposer.generated.h"

UCLASS()
class LETSGO_API AMusicComposer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Started = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void InitializeComposerData();
	
	UFUNCTION()
	void InitializeStrategies();
	
	IMusicStrategy* ChooseMusicalStrategy(const TSharedPtr<FComposerData>& ComposerDataPtr, float& AppropriatenessOut);
	
	FInstrumentSchedule GenerateBars(TSharedPtr<FComposerData>& ComposerData, IMusicStrategy* ChosenStrategy, int StartAtBar, int TimesToRepeat);

	UFUNCTION()
	void GenerateScale();

	UFUNCTION()
	void UpdateAllowableNoteIndices(int Interval);

	UFUNCTION()
	void CheckAndGenerateBars(int32 CurrentBar);

	UFUNCTION()
	void OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};
