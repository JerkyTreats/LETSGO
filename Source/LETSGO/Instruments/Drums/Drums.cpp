// Fill out your copyright notice in the Description page of Project Settings.


#include "Drums.h"

#include "DrumsAudioCuePlayer.h"
#include "Components/AudioComponent.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
ADrums::ADrums(): Clock(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstrumentMetaSoundSource = CreateDefaultSubobject<UMetaSoundSource>(TEXT("Meta Sound Source"));
	
	PlayQuantizationDelegate.BindUFunction(this, "OnQuantizationBoundaryTriggered");
}

// Called when the game starts or when spawned
void ADrums::BeginPlay()
{
	Super::BeginPlay();

	/** Gets a reference from the Quartz subsystem from the world. */
	UQuartzSubsystem* Quartz = GetWorld()->GetSubsystem<UQuartzSubsystem>();

	/** Defines settings for FQuartzTimeSignature and FQuartzClockSettings structures. */
	FQuartzTimeSignature TimeSignature;
	FQuartzClockSettings ClockSettings;
	ClockSettings.TimeSignature = TimeSignature;

	/** Creates a new clock the previous setting structures. */
	Clock = Quartz->CreateNewClock(this, ClockName, ClockSettings, true);
	/** Sets the tempo for the clock. */
	Clock->SetBeatsPerMinute(this, QuartzQuantizationBoundary, FOnQuartzCommandEventBP(), Clock, BPM);
	
	UE_LOG(LogTemp, Display, TEXT("Drums BeginPlay Complete"))
}

// Called every frame
void ADrums::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADrums::StartPlaying()
{
	Clock->StartClock(GetWorld(), Clock);
	Clock->SubscribeToQuantizationEvent(GetWorld(), QuartzQuantizationBoundary.Quantization, PlayQuantizationDelegate, Clock);
}

void ADrums::StopPlaying()
{
	Clock->UnsubscribeFromAllTimeDivisions(GetWorld(), Clock);
	Clock->StopClock(GetWorld(), true, Clock);
}

void ADrums::OnQuantizationBoundaryTriggered(FName DrumClockName, EQuartzCommandQuantization QuantizationType,
	int32 NumBars, int32 Beat, float BeatFraction)
{
	// AudioComponent.PlayQuantized() takes in a Quant Boundary, allowing you to schedule sound relative to the current Boundary
	// ie. If OnQuantTriggered fired per bar, this boundary can schedule something for next bar
	// We want to play right now
	const FQuartzQuantizationBoundary RelativeQuartzBoundary = {
		EQuartzCommandQuantization::None,
		1.0f,
		EQuarztQuantizationReference::BarRelative,
		true
	};

	// Play the kick drum sound
	// This creates an Actor wrapper around a new AudioComponent we want to play on this beat
	// This is so we can destroy the Actor after use
	ADrumsAudioCuePlayer* AudioCuePlayer = GetWorld()->SpawnActor<ADrumsAudioCuePlayer>();
	AudioCuePlayer->Initialize(InstrumentMetaSoundSource, Clock,RelativeQuartzBoundary);
	AudioCuePlayer->PlayAndDestroy();
	
}
