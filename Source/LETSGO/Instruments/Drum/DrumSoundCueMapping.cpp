// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumSoundCueMapping.h"


// Sets default values
ADrumSoundCueMapping::ADrumSoundCueMapping(): Kick(nullptr), Snare(nullptr), HiHatOpen(nullptr), HiHatClosed(nullptr),
                                              Clap(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADrumSoundCueMapping::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrumSoundCueMapping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

