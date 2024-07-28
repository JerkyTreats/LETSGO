// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "MetasoundSource.h"
#include "Drums.generated.h"

// See https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
UCLASS()
class LETSGO_API ADrums : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrums();

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	UQuartzClockHandle* Clock;

	UPROPERTY(BlueprintReadWrite, Category="LETSGO")
	UAudioComponent* InstrumentAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LETSGO")
	UMetaSoundSource* InstrumentMetaSoundSource;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
