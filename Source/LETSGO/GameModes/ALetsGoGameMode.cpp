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
