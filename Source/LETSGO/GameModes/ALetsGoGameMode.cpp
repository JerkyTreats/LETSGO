// Fill out your copyright notice in the Description page of Project Settings.

#include "ALetsGoGameMode.h"
#include "ALetsGoGameState.h"
#include "LETSGO/LETSGO.h"

ALetsGoGameMode::ALetsGoGameMode()
{
	GameStateClass = ALetsGoGameState::StaticClass();
	PhaseManager = CreateDefaultSubobject<APhaseManager>(TEXT("Phase Manager"));
}

void ALetsGoGameMode::BeginPlay()
{
	Super::BeginPlay();

	PhaseManager = GetWorld()->SpawnActor<APhaseManager>(PhaseManagerClass);
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALetsGoGameMode::InitializeGameplay,5.0f,false);
	UE_LOG(LogLetsgo, Display, TEXT("Wait 5"));
}

void ALetsGoGameMode::InitializeGameplay()
{
	UE_LOG(LogLetsgo, Display, TEXT("Initialize Gameplay"));
	PhaseManager->Initialize();
}

void ALetsGoGameMode::SetTonic(const FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Tonic = Note;
}

FLetsGoMusicNotes ALetsGoGameMode::GetTonic() const
{
	return GetGameState<ALetsGoGameState>()->Tonic;
}

AClockSettings* ALetsGoGameMode::GetClockSettings() const
{
	return GetGameState<ALetsGoGameState>()->ClockSettings;
}

void ALetsGoGameMode::SetClockSettings(AClockSettings* Clock)
{
	GetGameState<ALetsGoGameState>()->ClockSettings = Clock;
}

void ALetsGoGameMode::SetInstrumentRack(UInstrumentRack* Rack)
{
	GetGameState<ALetsGoGameState>()->InstrumentRack = Rack;
}

UInstrumentRack* ALetsGoGameMode::GetInstrumentRack()
{
	return GetGameState<ALetsGoGameState>()->InstrumentRack;
}
