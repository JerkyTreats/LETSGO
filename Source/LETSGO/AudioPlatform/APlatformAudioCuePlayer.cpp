﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "APlatformAudioCuePlayer.h"

#include "AAudioPlatform.h"
#include "Components/AudioComponent.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "Logging/StructuredLog.h"


class ALetsGoGameMode;
// Sets default values for this component's properties
APlatformAudioCuePlayer::APlatformAudioCuePlayer()
{
	Instrument = CreateDefaultSubobject<AInstrument>(TEXT("DefaultInstrument"));
}

// Called when the game starts
void APlatformAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Bind the On Platform Triggered Event to a local function
	AudioPlatformReference->OnAudioPlatformTriggered.AddDynamic(this, &APlatformAudioCuePlayer::OnAudioPlatformTriggered);
	
	CheeseKeyData = GetWorld()->SpawnActor<ACheeseKeySoundCueMapping>(CheeseKeyClass);
	Instrument = GetWorld()->SpawnActor<AInstrument>(InstrumentClass);

	// Set Instrument to play on next beat, defaults wait for next bar
	Instrument->QuartzQuantizationBoundary = QuartzQuantizationBoundary;
	Instrument->RelativeQuantizationResolution = EQuartzCommandQuantization::Beat;
	Instrument->RelativeQuantizationReference = EQuarztQuantizationReference::Count;
	
}

void APlatformAudioCuePlayer::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote)
{
	UE_LOG(LogLetsgo, Display, TEXT("AudioCuePlayer Recieved OnAudioPLatformTrigger"));
	
	const FInstrumentSchedule Schedule = BuildInstrumentSchedule(IncomingNote.Note);
	Instrument->InitializeSingleSchedule(Schedule);
	Instrument->Initialize();
}

FInstrumentSchedule APlatformAudioCuePlayer::BuildInstrumentSchedule(TEnumAsByte<ELetsGoMusicNotes> ENote) const
{
	int Octave = 3;

	// Filter the array
	TArray<FInstrumentNote> FilteredNotes = CheeseKeyData->NoteData.Notes.FilterByPredicate([&] (const FInstrumentNote& Data){
		return Data.Octave == Octave && Data.Note == ENote;
	});
	
	if (FilteredNotes.Num() != 1)
	{
		UE_LOG(LogLetsgo, Error, TEXT("FilteredNote predicate did not return 1 Note"))
		return FInstrumentSchedule();
	}

	FNotesPerBar NotesPerBar = FNotesPerBar(1.0f, FilteredNotes[0].SoundData);
	const TArray<FPerBarSchedule> PerBar = TArray {FPerBarSchedule({NotesPerBar}) };
	FInstrumentSchedule Schedule = FInstrumentSchedule(EQuartzCommandQuantization::Beat, PerBar, 0);
	return Schedule;
}

// Need this extra destroy function because AddDynamic complains if you try to call &AAudioCuePlayer::Destroy directly
void APlatformAudioCuePlayer::InitiateDestroy()
{
	if(IsSoundPlaying)
	{
		AttachedAudioComponent->OnAudioFinished.AddDynamic(this, &APlatformAudioCuePlayer::DestroyActor);
	}
	else
	{
		DestroyActor();
	}
}

void APlatformAudioCuePlayer::DestroyActor()
{
	Instrument->Destroy();
	Destroy();
}
