// Fill out your copyright notice in the Description page of Project Settings.


#include "APlatformAudioCuePlayer.h"

#include "AAudioPlatform.h"
#include "Components/AudioComponent.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "Logging/StructuredLog.h"


class ALetsGoGameMode;
// Sets default values for this component's properties
APlatformAudioCuePlayer::APlatformAudioCuePlayer()
{

}

// Called when the game starts
void APlatformAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Bind the On Platform Triggered Event to a local function
	AudioPlatformReference->OnAudioPlatformTriggered.AddDynamic(this, &APlatformAudioCuePlayer::OnAudioPlatformTriggered);
	
	CheeseKeyData = GetWorld()->SpawnActor<ACheeseKeySoundCueMapping>();
	Instrument = GetWorld()->SpawnActor<AInstrument>();
	
}

void APlatformAudioCuePlayer::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote)
{
	UE_LOG(LogTemp, Display, TEXT("AudioCuePlayer Recieved OnAudioPLatformTrigger"));
	
	FInstrumentSchedule Schedule = BuildInstrumentSchedule(IncomingNote.Note);
	Instrument->Initialize(Schedule);
	
}

// This is bad but requires a real solution to be figured out and implemented
FInstrumentSchedule APlatformAudioCuePlayer::BuildInstrumentSchedule(TEnumAsByte<ELetsGoMusicNotes> ENote) const
{
	int Octave = 2;
	// MyArrayOfInts.FindByPredicate([](int32 n){ return n % 1; }));
	TArray<FCheeseKeyData> FilteredNotes = CheeseKeyData->NoteData.FilterByPredicate([](FCheeseKeyData KeyData, TEnumAsByte<ELetsGoMusicNotes> Note = ENote, int Oct = Octave)
	{
		return KeyData.Note == Note && KeyData.Octave == Oct;
	});

	if (FilteredNotes.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("FilteredNote predicate did not return 1 Note"))
		return FInstrumentSchedule();
	}

	FCheeseKeyData Note = FilteredNotes[0];
	FPerBarSchedule PerBar = FPerBarSchedule(Note.Sound,{1.0f});
	FInstrumentSchedule Schedule = FInstrumentSchedule(EQuartzCommandQuantization::Beat, {PerBar});
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
	Destroy();
}
