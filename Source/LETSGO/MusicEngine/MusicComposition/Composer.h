// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "Composer.generated.h"

USTRUCT()
struct FComposerData
{
	GENERATED_BODY()

	int NumBarsToCompose;
	FLetsGoGeneratedScale Scale;
	int OctaveMin = 1;
	int OctaveMax = 5;
	
};

UCLASS()
class LETSGO_API AComposer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AComposer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FInstrumentSchedule ComposeInstrumentSchedule(FComposerData Data);
};
