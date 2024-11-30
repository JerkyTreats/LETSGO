// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/Cheese Keys/CheeseKeySoundCueMapping.h"
#include "LETSGO/Instruments/Drum/DrumSoundCueMapping.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "MusicComposerState.generated.h"

UCLASS()
class LETSGO_API AMusicComposerState : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMusicComposerState();
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 BarCreationThreshold = 4;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MusicalStrategyAppropriatenessThreshold = 0.4f;
	
	UPROPERTY()
	FLetsGoGeneratedScale Scale;

	UPROPERTY()
	bool IsTonicSet = false;

	UPROPERTY()
	TArray<int> AllowableNoteIndices;

	TSharedPtr<TArray<FComposerData>> ComposerDataObjects;

	UPROPERTY()
	ACheeseKeySoundCueMapping* CheeseKeySoundCueMapping;

	UPROPERTY()
	ADrumSoundCueMapping* DrumsSoundCueMapping;

	UPROPERTY()
	int CurrentBar;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize();
};
