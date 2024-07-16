// Fill out your copyright notice in the Description page of Project Settings.

#include "ALetsGoGameMode.h"
#include "ALetsGoGameState.h"

ALetsGoGameMode::ALetsGoGameMode()
{
	GameStateClass = ALetsGoGameState::StaticClass();
	PhaseManager = CreateDefaultSubobject<UPhaseManager>(TEXT("Phase Manager"));
}

void ALetsGoGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	PhaseManager->Initialize(GetWorld());
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALetsGoGameMode::InitializeGameplay,5.0f,false);
	UE_LOG(LogTemp, Display, TEXT("Wait 5"));
}

void ALetsGoGameMode::SetTonic(const FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Tonic = Note;
}

UQuartzClockHandle* ALetsGoGameMode::GetMainClock() const
{
	return GetGameState<ALetsGoGameState>()->MainClock;
}

void ALetsGoGameMode::SetMainClock(UQuartzClockHandle* Clock)
{
	GetGameState<ALetsGoGameState>()->MainClock = Clock;
}

void ALetsGoGameMode::InitializeGameplay()
{
	UE_LOG(LogTemp, Display, TEXT("Enabling Tick"));
	PhaseManager->BeginTicking();
}
