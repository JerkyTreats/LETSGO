// Fill out your copyright notice in the Description page of Project Settings.


#include "Phase_StartMusicComposer.h"

#include "MusicComposer.h"


// Sets default values
APhase_StartMusicComposer::APhase_StartMusicComposer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APhase_StartMusicComposer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhase_StartMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhase_StartMusicComposer::Initialize()
{
	AMusicComposer* MusicComposer = GetWorld()->SpawnActor<AMusicComposer>();
}

void APhase_StartMusicComposer::Activate()
{
}

bool APhase_StartMusicComposer::IsActivated()
{
	return Active;
}

void APhase_StartMusicComposer::Deactivate()
{
}

void APhase_StartMusicComposer::Complete()
{
}

bool APhase_StartMusicComposer::IsCompleted()
{
	return Completed;
}

void APhase_StartMusicComposer::InitiateDestroy()
{
}

