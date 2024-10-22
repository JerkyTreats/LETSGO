// Fill out your copyright notice in the Description page of Project Settings.


#include "Instrument.h"
#include "LETSGO/MusicEngine/ClockSettings.h"
#include "AudioCuePlayer.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"


// Sets default values
AInstrument::AInstrument(): Clock(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayQuantizationDelegate.BindUFunction(this, "OnQuantizationBoundaryTriggered");
}

// Called when the game starts or when spawned
void AInstrument::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogLetsgo, Display, TEXT("Instrument BeginPlay Complete"))
}

void AInstrument::BeginDestroy()
{
	if (Clock)
		Clock->StopClock(GetWorld(), true, Clock);
	
	Super::BeginDestroy();

	// 
	//InstrumentSchedules.Empty();
}

void AInstrument::InitializeClock()
{
	// Build Clock Name
	FString Name = GetName();
	Name = Name.Append("_Clock");
	
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	ClockSettings = GameMode->GetClockSettings();

	Clock = ClockSettings->GetNewClock(FName(Name));

	Clock->StartClock(GetWorld(), Clock);
	Clock->SubscribeToQuantizationEvent(GetWorld(), QuartzQuantizationBoundary.Quantization, PlayQuantizationDelegate, Clock);
}

// Called every frame
void AInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInstrument::Initialize(const bool IsRepeating, const int InCurrentBar)
{
	InitializeClock();
	Repeat = IsRepeating;
	CurrentBar = InCurrentBar;
}

void AInstrument::InitializeSingleSchedule(const FInstrumentSchedule& Schedule)
{
	TArray Schedules = {Schedule};
	InstrumentSchedules = MakeShared<TArray<FInstrumentSchedule>>(Schedules) ;
}

void AInstrument::InitializeMultipleSchedules(TSharedPtr<TArray<FInstrumentSchedule>> Schedules)
{
	InstrumentSchedules = Schedules;
}

void AInstrument::PlayBar(const int BarIndexToPlay, const FInstrumentSchedule& InstrumentSchedule)
{
	if (BarIndexToPlay >= InstrumentSchedule.BeatSchedule.Num())
	{
		UE_LOG(LogLetsgo, Error, TEXT("Instrument PlayBar exceeded index"))
		return;
	} 
	
	const FPerBarSchedule BarSchedule = InstrumentSchedule.BeatSchedule[BarIndexToPlay];

	for (int i = 0; i < BarSchedule.NotesInBar.Num(); i++)
	{
		const FNotesPerBar Notes = BarSchedule.NotesInBar[i];
		
		const FQuartzQuantizationBoundary RelativeQuartzBoundary = {
			InstrumentSchedule.QuantizationDivision,
			Notes.Beat,
			RelativeQuantizationReference,
			true
		};

		// Play the sound
		// This creates an Actor wrapper around a new AudioComponent we want to play on this beat
		// This is so we can easily destroy the Actor after use
		AAudioCuePlayer* AudioCuePlayer = GetWorld()->SpawnActor<AAudioCuePlayer>(AudioCueClass);
		AudioCuePlayer->Initialize(Notes.SoundData, Clock, RelativeQuartzBoundary);
		AudioCuePlayer->PlayAndDestroy();
	}
}

void AInstrument::OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType,
                                                  int32 NumBars, int32 Beat, float BeatFraction)
{
	if (InstrumentSchedules->Num() == 0)
		return;

	const FInstrumentSchedule InstrumentSchedule = (*InstrumentSchedules)[InstrumentScheduleIndex];

	if (InstrumentSchedule.StartAtBar < CurrentBar)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Bar [%i], StartAtBar [%i]"), CurrentBar, InstrumentSchedule.StartAtBar ));
	}

	const int CurrentRelativeBar = CurrentBar - InstrumentSchedule.StartAtBar;
	const int AbsoluteEnd = InstrumentSchedule.StartAtBar + InstrumentSchedule.BeatSchedule.Num() - 1;

	if (CurrentBar <= AbsoluteEnd)
	{
		PlayBar(CurrentRelativeBar, InstrumentSchedule);
	}

	if (CurrentBar >= AbsoluteEnd)
	{
		if (Repeat)
		{
			InstrumentScheduleIndex = 0;
			CurrentBar = 0;
			return;
		}

		if (InstrumentSchedules->Num() != InstrumentScheduleIndex + 1)
		{
			InstrumentScheduleIndex++;
		}
	}
	
	CurrentBar++;
}

void AInstrument::InitiateDestroy()
{
	Destroy();
}
