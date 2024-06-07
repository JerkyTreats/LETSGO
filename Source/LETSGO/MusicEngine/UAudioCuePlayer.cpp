// Fill out your copyright notice in the Description page of Project Settings.


#include "UAudioCuePlayer.h"

#include "AAudioPlatform.h"
#include "Components/AudioComponent.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "Logging/StructuredLog.h"


class ALetsGoGameMode;
// Sets default values for this component's properties
UAudioCuePlayer::UAudioCuePlayer()
{
	/**
	 * Creates an audio component.
	 *  Audio component needed in order to play the sound quantized
	 */
	AttachedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Attached Audio Component"));
	AttachedAudioComponent->SetAutoActivate(false); // Don't play immediately
	AttachedAudioComponent->bAllowSpatialization = false; // Don't play in world


	// Generate the map for notes -> sound cue
	NoteCueMap.Add(ELetsGoMusicNotes::A, A2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::AFlat, AFlat2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::BFlat, BFlat2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::B, B_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::C, C3_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::CSharp, CSharp3_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::D, D2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::EFlat, EFlat2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::E, E2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::F, F2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::FSharp, FSharp2_Music_Note);
	NoteCueMap.Add(ELetsGoMusicNotes::G, G2_Music_Note);
}


// Called when the game starts
void UAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Bind function that fires when Audio is finished playing
	AttachedAudioComponent->OnAudioFinished.AddDynamic(this, &UAudioCuePlayer::OnAudioCueFinished);
	
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Clock = GameMode->GetMainClock();

	// Subscribe to Clock events (beat, bar, whole, etc.)
	Clock->SubscribeToAllQuantizationEvents(GetWorld(), ExecuteInClockTimeDelegate, Clock);


}

void UAudioCuePlayer::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote)
{
	USoundCue* ThisSoundCue = GetSoundCue(IncomingNote.Note);
	AttachedAudioComponent->SetSound(ThisSoundCue);

	const FOnQuartzCommandEventBP EmptyOnQuartzCommandEventBP; 
	AttachedAudioComponent->PlayQuantized(GetWorld(),Clock, QuartzQuantizationBoundary, EmptyOnQuartzCommandEventBP);
	
}

// This is bad but requires a real solution to be figured out and implemented
USoundCue* UAudioCuePlayer::GetSoundCue(TEnumAsByte<ELetsGoMusicNotes> ENote) const
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

void UAudioCuePlayer::OnAudioCueFinished()
{
	ReadyForCleanUp.Broadcast();
}

// Called every frame
void UAudioCuePlayer::TickComponent(float DeltaTime, ELevelTick TickType,
									   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAudioCuePlayer::Initialize(AAudioPlatform* AudioPlatform, const FQuartzQuantizationBoundary& Boundary)
{
	QuartzQuantizationBoundary = Boundary;
	AudioPlatformReference = AudioPlatform;
	// Bind the On Platform Triggered Event to a local function
	AudioPlatformReference->OnAudioPlatformTriggered.AddDynamic(this, &UAudioCuePlayer::OnAudioPlatformTriggered);
}
