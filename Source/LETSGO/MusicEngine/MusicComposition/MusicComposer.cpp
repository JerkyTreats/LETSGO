// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"

#include "PedalPoint_MusicalStrategy.h"


// Sets default values
AMusicComposer::AMusicComposer(): CompositionStrategies()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMusicComposer::BeginPlay()
{
	Super::BeginPlay();

	IMusicCompositionStrategy* PedalPoint = NewObject<UPedalPoint_MusicalStrategy>();

	CompositionStrategies.Emplace(PedalPoint);
}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMusicComposer::Initialize()
{
	
}

FInstrumentSchedule AMusicComposer::ComposeInstrumentSchedule()
{
	
}
