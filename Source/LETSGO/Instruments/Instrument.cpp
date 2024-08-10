// Fill out your copyright notice in the Description page of Project Settings.


#include "Instrument.h"
#include "LETSGO/MusicEngine/ClockSettings.h"
#include "AudioCuePlayer.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"


// Sets default values
AInstrument::AInstrument(): Clock(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstrumentMetaSoundSource = CreateDefaultSubobject<UMetaSoundSource>(TEXT("Meta Sound Source"));
	
	PlayQuantizationDelegate.BindUFunction(this, "OnQuantizationBoundaryTriggered");
}

// Called when the game starts or when spawned
void AInstrument::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Drums BeginPlay Complete"))
}

void AInstrument::SetClock()
{
	// Build Clock Name
	FString Name = GetName();
	Name = Name.Append("_Clock");
	
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	ClockSettings = GameMode->GetClockSettings();

	Clock = ClockSettings->GetNewClock(FName(Name));
}

// Called every frame
void AInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInstrument::Initialize(FInstrumentSchedule Schedule, UMetaSoundSource* MetaSoundSource)
{
	SetClock();
	InstrumentMetaSoundSource = MetaSoundSource;
	InstrumentSchedule = Schedule;
	RelativeQuantizationResolution = Schedule.QuantizationDivision; 
}

void AInstrument::StartPlaying()
{
	Clock->StartClock(GetWorld(), Clock);
	Clock->SubscribeToQuantizationEvent(GetWorld(), QuartzQuantizationBoundary.Quantization, PlayQuantizationDelegate, Clock);
}

void AInstrument::StopPlaying()
{
	Clock->UnsubscribeFromAllTimeDivisions(GetWorld(), Clock);
	Clock->StopClock(GetWorld(), true, Clock);
}

void AInstrument::OnQuantizationBoundaryTriggered(FName DrumClockName, EQuartzCommandQuantization QuantizationType,
	int32 NumBars, int32 Beat, float BeatFraction)
{
	FPerBarSchedule ThisBar = InstrumentSchedule.BeatSchedule[CurrentBar];

	for (int i = 0; i < ThisBar.BeatsInBar.Num(); i++)
	{
		const FQuartzQuantizationBoundary RelativeQuartzBoundary = {
			RelativeQuantizationResolution,
			ThisBar.BeatsInBar[i],
			EQuarztQuantizationReference::BarRelative,
			true
		};

		// Play the kick drum sound
		// This creates an Actor wrapper around a new AudioComponent we want to play on this beat
		// This is so we can destroy the Actor after use
		AAudioCuePlayer* AudioCuePlayer = GetWorld()->SpawnActor<AAudioCuePlayer>();
		AudioCuePlayer->Initialize(InstrumentMetaSoundSource, Clock,RelativeQuartzBoundary);
		AudioCuePlayer->PlayAndDestroy();
	}

	if (CurrentBar == InstrumentSchedule.BeatSchedule.Num() - 1)
	{
		CurrentBar = 0;
	}
	else
	{
		CurrentBar++;
	}
}
