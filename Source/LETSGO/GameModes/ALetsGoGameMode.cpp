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

	State = GetGameState<ALetsGoGameState>();

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

// Tonic 
void ALetsGoGameMode::SetTonic(const FLetsGoMusicNotes Note) const
{
	State->Tonic = Note;
	State->ChromaticScale = FLetsGoGeneratedScale(Note, ULetsGoMusicEngine::Chromatic);
	State->IsTonicSet = true;

	OnTonicSet.Broadcast();
}

FLetsGoMusicNotes ALetsGoGameMode::GetTonic() const
{
	if (! State->IsTonicSet)
		UE_LOG(LogLetsgo, Error, TEXT("GameMode GetTonic Called before set."))

	return State->Tonic;
}

FLetsGoGeneratedScale ALetsGoGameMode::GetChromaticScale() const
{
	if (! State->IsTonicSet)
		UE_LOG(LogLetsgo, Error, TEXT("GameMode GetChromaticScale called before set."))
	
	return State->ChromaticScale;
}

void ALetsGoGameMode::SetInterval(const int Interval) const
{
	OnIntervalSet.Broadcast(Interval);
}

// Clock
AClockSettings* ALetsGoGameMode::GetClockSettings() const
{
	return State->ClockSettings;
}

void ALetsGoGameMode::SetClockSettings(AClockSettings* Clock)
{
	State->ClockSettings = Clock;
}

void ALetsGoGameMode::SetInstrumentRack(UInstrumentRack* Rack)
{
	State->InstrumentRack = Rack;
}

UInstrumentRack* ALetsGoGameMode::GetInstrumentRack()
{
	return State->InstrumentRack;
}

void ALetsGoGameMode::SetInstrumentData_CheeseKey(ACheeseKeySoundCueMapping* DataToSet)
{
	State->InstrumentData_CheeseKey = DataToSet;
}

ACheeseKeySoundCueMapping* ALetsGoGameMode::GetInstrumentData_CheeseKey()
{
	ACheeseKeySoundCueMapping* DataMap = State->InstrumentData_CheeseKey;
	if (! DataMap)
	{
		UE_LOG(LogLetsgo, Error, TEXT("InstrumentData_CheeseKey not set in State, returning nullptr"))
	}
	return DataMap;
}

void ALetsGoGameMode::SetInstrumentData_Drums(ADrumSoundCueMapping* DataToSet)
{
	State->InstrumentData_Drums = DataToSet;
}

ADrumSoundCueMapping* ALetsGoGameMode::GetInstrumentData_Drums()
{
	ADrumSoundCueMapping* DataMap = State->InstrumentData_Drums;
	if (! DataMap)
	{
		UE_LOG(LogLetsgo, Error, TEXT("InstrumentData_Drums not set in State, returning nullptr"))
	}
	return DataMap;
}

AMusicComposer* ALetsGoGameMode::GetMusicComposer()
{
	return State->MusicComposer;
}

void ALetsGoGameMode::SetMusicComposer(AMusicComposer* Composer)
{
	State->MusicComposer = Composer;
}
