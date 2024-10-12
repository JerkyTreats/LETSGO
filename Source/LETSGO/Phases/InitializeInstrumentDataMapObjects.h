// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/Cheese Keys/CheeseKeySoundCueMapping.h"
#include "LETSGO/Instruments/Drum/DrumSoundCueMapping.h"
#include "InitializeInstrumentDataMapObjects.generated.h"

UCLASS()
class LETSGO_API AInitializeInstrumentDataMapObjects : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInitializeInstrumentDataMapObjects();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<ADrumSoundCueMapping> ADrumSoundCueMappingClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<ACheeseKeySoundCueMapping> CheeseKeyMappingClass ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();
};
