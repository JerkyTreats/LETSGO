// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioCuePlayer.h"

#include "AAudioPlatform.h"
#include "Components/AudioComponent.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "Logging/StructuredLog.h"


class ALetsGoGameMode;
// Sets default values for this component's properties
AAudioCuePlayer::AAudioCuePlayer()
{
	/**
	 * Creates an audio component.
	 *  Audio component needed in order to play the sound quantized
	 */
	AttachedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Attached Audio Component"));
	AttachedAudioComponent->SetAutoActivate(false); // Don't play immediately
	AttachedAudioComponent->bAllowSpatialization = false; // Don't play in world

}


// Called when the game starts
void AAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Bind the On Platform Triggered Event to a local function
	AudioPlatformReference->OnAudioPlatformTriggered.AddDynamic(this, &AAudioCuePlayer::OnAudioPlatformTriggered);
	
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Clock = GameMode->GetMainClock();
	
}

void AAudioCuePlayer::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote)
{
	USoundCue* ThisSoundCue = GetSoundCue(IncomingNote.Note);
	AttachedAudioComponent->SetSound(ThisSoundCue);

	const FOnQuartzCommandEventBP EmptyOnQuartzCommandEventBP; 
	AttachedAudioComponent->PlayQuantized(GetWorld(),Clock, QuartzQuantizationBoundary, EmptyOnQuartzCommandEventBP);
}

// This is bad but requires a real solution to be figured out and implemented
USoundCue* AAudioCuePlayer::GetSoundCue(TEnumAsByte<ELetsGoMusicNotes> ENote) const
{
	switch (ENote)
	{
	case ELetsGoMusicNotes::A:
		return A2_Music_Note;
	case ELetsGoMusicNotes::AFlat:
		return AFlat2_Music_Note;
	case ELetsGoMusicNotes::B:
		return B_Music_Note;
	case ELetsGoMusicNotes::BFlat:
		return BFlat2_Music_Note;
	case ELetsGoMusicNotes::C:
		return CSharp3_Music_Note;
	case ELetsGoMusicNotes::CSharp:
		return CSharp3_Music_Note;
	case ELetsGoMusicNotes::D:
		return D2_Music_Note;
	case ELetsGoMusicNotes::EFlat:
		return EFlat2_Music_Note;
	case ELetsGoMusicNotes::E:
		return E2_Music_Note;
	case ELetsGoMusicNotes::F:
		return FSharp2_Music_Note;
	case ELetsGoMusicNotes::FSharp:
		return FSharp2_Music_Note;
	case ELetsGoMusicNotes::G:
		return G2_Music_Note;
	default:
		// TODO Build Custom Logging Section
		UE_LOGFMT(LogTemp, Error, "Note does not exist in AudioCuePlayer::NoteCueMap");
		return CSharp3_Music_Note;
	}
}
