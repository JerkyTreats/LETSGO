// Fill out your copyright notice in the Description page of Project Settings.


#include "StartClock.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/MusicEngine/ClockSettings.h"


// Sets default values
AStartClock::AStartClock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AStartClock::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStartClock::Initialize()
{
	AClockSettings* MainClock = GetWorld()->SpawnActor<AClockSettings>(ClockSettingsClass);
	
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetClockSettings(MainClock);
}

void AStartClock::Activate()
{
	IsActive = true;
	Complete();
}

bool AStartClock::IsActivated()
{
	return IsActive;
}

void AStartClock::Deactivate()
{
	IsActive = false;
}

// Not expecting this phase to end?
void AStartClock::Complete()
{
	IsComplete = true;
	Deactivate();
}

// Not expecting this phase to end?
bool AStartClock::IsCompleted()
{
	return IsComplete;
}

void AStartClock::InitiateDestroy()
{
	Destroy();
}

// Called every frame
void AStartClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

