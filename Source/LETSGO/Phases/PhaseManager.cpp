// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"

#include "SetTonic.h"
#include "Sleep.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "StartDrums.h"
#include "StartMusicComposer.h"
#include "LETSGO/MusicEngine/MusicComposition/MusicComposer.h"
#include "LETSGO/Phases/StartClock.h"

APhaseManager::APhaseManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Phases = TArray<IPhaseController*>();
}

void APhaseManager::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	/*
	UInstrumentRack* InstrumentRack = NewObject<UInstrumentRack>();
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetInstrumentRack(InstrumentRack);
	*/
	
	AStartClock* StartClock = World->SpawnActor<AStartClock>(StartClockClass);
	StartClock->Initialize();
	Phases.Emplace(StartClock);

	AInitializeInstrumentDataMapObjects* InitInstrumentDataMaps = World->SpawnActor<AInitializeInstrumentDataMapObjects>(InitializeDataMapClass);
	InitInstrumentDataMaps->Initialize();
	
	AStartMusicComposer* MusicComposer = World->SpawnActor<AStartMusicComposer>(StartMusicComposerClass);
	MusicComposer->Initialize();
	Phases.Emplace(MusicComposer);
	
	AStartDrums* StartDrums = World->SpawnActor<AStartDrums>(StartDrumsClass);
	StartDrums->Initialize();
	Phases.Emplace(StartDrums); 

	ASetTonic* SetTonic = World->SpawnActor<ASetTonic>(SetTonicClass);
	SetTonic->Initialize();
	Phases.Emplace(SetTonic);

	ASleep* Sleep = World -> SpawnActor<ASleep>();
	Phases.Emplace(Sleep);

	ASetThird* SetThird = World->SpawnActor<ASetThird>(SetThirdClass);
	SetThird->Initialize();
	Phases.Emplace(SetThird);

	UE_LOG(LogLetsgo, Display, TEXT("PhaseManager BeginPlay complete"));

}

void APhaseManager::Initialize()
{
	TickEnabled = true;
}

void APhaseManager::ProcessPhases()
{

	
	if (Phases.Num() == 0)
	{
		if (EmptyListWarnAmount < 5)
		{
			// TODO create custom Log Category 
			UE_LOG(LogLetsgo, Warning, TEXT("Empty Phase List"));
			EmptyListWarnAmount++;
			
			if (EmptyListWarnAmount == 5 )
			{
				UE_LOG(LogLetsgo, Warning, TEXT("Disabling Empty Phase List Warning."));
			}
		}
		return;
	}
	
	EmptyListWarnAmount = 0;

	if (Phases[0]->IsCompleted())
	{
		IPhaseController* Completed = Phases[0];
		Phases.RemoveAt(0);
		Completed->InitiateDestroy();
	}

	if (Phases.Num() == 0)
	{
		UE_LOG(LogLetsgo, Warning, TEXT("Last Phase In Phase List Completed"));
		return;
	}

	// Activate next phase
	if ( Phases.Num() > 0 && ! Phases[0]->IsActivated())
	{
		Phases[0]->Activate();
	}
}

void APhaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TickEnabled)
	{
		ProcessPhases();
	}
}


