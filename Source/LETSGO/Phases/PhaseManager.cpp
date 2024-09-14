// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"

#include "SetTonic.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/Instruments/StartDrums.h"
#include "LETSGO/Phases/StartClock.h"

APhaseManager::APhaseManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Phases = TArray<IPhaseController*>();
}

void APhaseManager::BeginPlay()
{
	Super::BeginPlay();

	UInstrumentRack* InstrumentRack = NewObject<UInstrumentRack>();
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetInstrumentRack(InstrumentRack);
	
	AStartClock* StartClock = GetWorld()->SpawnActor<AStartClock>(StartClockClass);
	StartClock->Initialize();
	Phases.Emplace(StartClock);

	AStartDrums* StartDrums = GetWorld()->SpawnActor<AStartDrums>(StartDrumsClass);
	StartDrums->Initialize();
	Phases.Emplace(StartDrums);
	
	ASetTonic* SetTonic = GetWorld()->SpawnActor<ASetTonic>(SetTonicClass);
	SetTonic->Initialize();
	Phases.Emplace(SetTonic);

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


