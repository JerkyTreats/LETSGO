// Fill out your copyright notice in the Description page of Project Settings.


#include "UAudioCuePlayer.h"

#include "AAudioPlatform.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


class ALetsGoGameMode;
// Sets default values for this component's properties
UAudioCuePlayer::UAudioCuePlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Metronome
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Clock = GameMode->GetMainClock();

	// Bind to FAudioPlatformTriggerDelegate
	AudioPlatformReference->OnAudioPlatformTriggered.AddDynamic(this, &UAudioCuePlayer::OnAudioPlatformTriggered);

	/** Defines settings for the FQuartzQuantizationBoundary structure. */
	FQuartzQuantizationBoundary QuartzQuantizationBoundary;
	QuartzQuantizationBoundary.Quantization = EQuartzCommandQuantization::Bar;
	QuartzQuantizationBoundary.Multiplier = 1.0f;
	QuartzQuantizationBoundary.CountingReferencePoint = EQuarztQuantizationReference::BarRelative;
	QuartzQuantizationBoundary.bResetClockOnQueued = true;

	/*
	 *  1. Get Main Clock
	 *  2. Subscribe to Quantization Event
	 *		a. Clock
	 *		b. In Quantization Boundary
	 *		c. On Quantization Event Delegate
	 *  3. On Audio Platform Triggered
	 *		a. Map Note to Audio Cue
	 *		b. Play Quantized Audio Cue
	 *
	 * 
	 */
}

void UAudioCuePlayer::OnAudioPlatformTriggered(FLetsGoMusicNotes Note)
{
	PlayNote(Note);
}

void UAudioCuePlayer::PlayNote(FLetsGoMusicNotes Note)
{

	// Clock->SubscribeToQuantizationEvent(GetWorld(),EQuartzCommandQuantization::Bar,)
}

void UAudioCuePlayer::OnBar(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat,
	float BeatFraction)
{
}

void UAudioCuePlayer::FPlayQuantizedDelegate(EQuartzCommandDelegateSubType EventType, FName Name)
{
}

// Called every frame
void UAudioCuePlayer::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

