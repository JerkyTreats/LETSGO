// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMusicConductor.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AStartMusicConductor::AStartMusicConductor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStartMusicConductor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartMusicConductor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStartMusicConductor::Initialize()
{
	Conductor = GetWorld()->SpawnActor<AMusicConductor>(MusicConductorClass);

}

void AStartMusicConductor::Activate()
{
	Conductor->Initialize();

	Active = true;
	Completed = true;
}

bool AStartMusicConductor::IsActivated()
{
	return Active;
}

void AStartMusicConductor::Deactivate()
{
}

void AStartMusicConductor::Complete()
{
}

bool AStartMusicConductor::IsCompleted()
{
	return Completed;
}

void AStartMusicConductor::InitiateDestroy()
{
}

