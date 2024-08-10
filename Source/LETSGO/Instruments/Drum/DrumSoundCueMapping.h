// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetasoundSource.h"
#include "GameFramework/Actor.h"
#include "DrumSoundCueMapping.generated.h"

UCLASS()
class LETSGO_API ADrumSoundCueMapping : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrumSoundCueMapping();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	UMetaSoundSource* Kick;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	UMetaSoundSource* Snare;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	UMetaSoundSource* HiHatOpen;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	UMetaSoundSource* HiHatClosed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	UMetaSoundSource* Clap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
