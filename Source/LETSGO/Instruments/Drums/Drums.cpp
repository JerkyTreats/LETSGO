// Fill out your copyright notice in the Description page of Project Settings.


#include "Drums.h"

#include "Components/AudioComponent.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
ADrums::ADrums(): Clock(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstrumentAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	InstrumentAudioComponent->SetAutoActivate(false);
	InstrumentAudioComponent->SetSound(InstrumentMetaSoundSource);

	PlayQuantizationDelegate.BindUFunction(this, "FPlayQuantizedDelegate");
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
	Clock->SetBeatsPerMinute(this, FQuartzQuantizationBoundary(), FOnQuartzCommandEventBP(), Clock, BPM);

	/** Defines settings for the FQuartzQuantizationBoundary structure. */
	FQuartzQuantizationBoundary QuartzQuantizationBoundary;
	QuartzQuantizationBoundary.Quantization = EQuartzCommandQuantization::Bar;
	QuartzQuantizationBoundary.Multiplier = 1.0f;
	QuartzQuantizationBoundary.CountingReferencePoint = EQuarztQuantizationReference::BarRelative;
	QuartzQuantizationBoundary.bResetClockOnQueued = true;

	/** Plays the music cue from the audio component after the audio is "Queued" and loaded. Starts the clock. */
	InstrumentAudioComponent->PlayQuantized(this, Clock, QuartzQuantizationBoundary, PlayQuantizationDelegate);
}

// Called every frame
void ADrums::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
