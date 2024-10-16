// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicConductor.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AMusicConductor::AMusicConductor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuantizationDelegate.BindUFunction(this, "OnQuantizationBoundaryTriggered");
}

// Called when the game starts or when spawned
void AMusicConductor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMusicConductor::BeginDestroy()
{
	if (ConductorDatas.Num() > 0)
		ConductorDatas.Empty();

	
	Super::BeginDestroy();
}

void AMusicConductor::SetClock()
{
	// Build Clock Name
	FString Name = GetName();
	Name = Name.Append("_Clock");
	
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	const AClockSettings* ClockSettings = GameMode->GetClockSettings();

	Clock = ClockSettings->GetNewClock(FName(Name));
}

// Called every frame
void AMusicConductor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMusicConductor::Initialize()
{
	const UWorld* World = GetWorld();
	SetClock();
	Clock->StartClock(World, Clock);
	Clock->SubscribeToQuantizationEvent(GetWorld(), EQuartzCommandQuantization::Bar, QuantizationDelegate, Clock);

	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(World->GetAuthGameMode());
	const AMusicComposer* Composer = GameMode->GetMusicComposer();
	ComposerState = Composer->ComposerState;
	
	for(int i = 0; i < ComposerState->ComposerDataObjects.Num(); i++)
	{
		AInstrument* Instrument = GetWorld()->SpawnActor<AInstrument>();
		Instrument->InitializeMultipleSchedules(ComposerState->ComposerDataObjects[i].ScheduleData);
		
		ConductorDatas.Emplace(
			MakeShared<FComposerData>(ComposerState->ComposerDataObjects[i]),
			Instrument
		);
		Instrument->Initialize(false, ComposerState->CurrentBar);
	}
}

void AMusicConductor::OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType,
                                                      int32 NumBars, int32 Beat, float BeatFraction)
{
	ComposerState->CurrentBar = NumBars;
}

