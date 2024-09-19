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

// MUSICAL STATE
#pragma region MusicalState

// Tonic 
void ALetsGoGameMode::SetTonic(const FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Tonic = Note;
	OnMusicalStateUpdated.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetTonic() const
{
	return GetGameState<ALetsGoGameState>()->Tonic;
}

// Second
void ALetsGoGameMode::SetSecond(FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Second = Note;
	OnMusicalStateUpdated.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetSecond() const
{
	return GetGameState<ALetsGoGameState>()->Second;
}

// Third
void ALetsGoGameMode::SetThird(FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Third = Note;
	OnMusicalStateUpdated.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetThird() const
{
	return GetGameState<ALetsGoGameState>()->Third;
}

// Fourth
void ALetsGoGameMode::SetFourth(FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Fourth = Note;
	OnMusicalStateUpdated.Broadcast();
}


FLetsGoMusicNotes ALetsGoGameMode::GetFourth() const
{
	return GetGameState<ALetsGoGameState>()->Fourth;
}

// Fifth
void ALetsGoGameMode::SetFifth(FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Fifth = Note;
	OnMusicalStateUpdated.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetFifth() const
{
	return GetGameState<ALetsGoGameState>()->Fifth;
}

// Sixth
void ALetsGoGameMode::SetSixth(FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Sixth = Note;
	OnMusicalStateUpdated.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetSixth() const
{
	return GetGameState<ALetsGoGameState>()->Sixth;
}

// Seventh
void ALetsGoGameMode::SetSeventh(FLetsGoMusicNotes Note) const
{
	GetGameState<ALetsGoGameState>()->Seventh = Note;
	OnMusicalStateUpdated.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetSeventh() const
{
	return GetGameState<ALetsGoGameState>()->Seventh;
}

#pragma endregion  


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

void ALetsGoGameMode::SetInstrumentData_CheeseKey(ACheeseKeySoundCueMapping* DataToSet)
{
	GetGameState<ALetsGoGameState>()->InstrumentData_CheeseKey = DataToSet;
}

ACheeseKeySoundCueMapping* ALetsGoGameMode::GetInstrumentData_CheeseKey()
{
	ACheeseKeySoundCueMapping* CheeseKey = GetGameState<ALetsGoGameState>()->InstrumentData_CheeseKey;
	if (! CheeseKey)
	{
		UE_LOG(LogLetsgo, Error, TEXT("InstrumentData_CheeseKey not set in State, returning nullptr"))
	}
	return CheeseKey;
}

AMusicComposer* ALetsGoGameMode::GetMusicComposer()
{
	return GetGameState<ALetsGoGameState>()->MusicComposer;
}

void ALetsGoGameMode::SetMusicComposer(AMusicComposer* Composer)
{
	GetGameState<ALetsGoGameState>()->MusicComposer = Composer;
}
