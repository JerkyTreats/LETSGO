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
	/** Creates an audio component. */
	AttachedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Attached Audio Component"));
	AttachedAudioComponent->SetAutoActivate(false); // Don't play immediately
	AttachedAudioComponent->bAllowSpatialization = false; // Don't play in world
	
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ExecuteInClockTimeDelegate.BindUFunction(this, "FExecuteInClockTime");

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

	// Bind to FAudioPlatformTriggerDelegate
	AudioPlatformReference->OnAudioPlatformTriggered.AddDynamic(this, &UAudioCuePlayer::OnAudioPlatformTriggered);
	
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Clock = GameMode->GetMainClock();

	// Subscribe to Clock events (beat, bar, whole, etc.)
	Clock->SubscribeToAllQuantizationEvents(GetWorld(), ExecuteInClockTimeDelegate, Clock);
	
}

void UAudioCuePlayer::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote)
{
	Note = IncomingNote;
	
	USoundCue* ThisSoundCue = GetSoundCue(Note.Note);
	AttachedAudioComponent->SetSound(ThisSoundCue);
	
	FExecuteInClockTime("", EQuartzCommandQuantization::None, 0, 0, 0);
	
}

void UAudioCuePlayer::FExecuteInClockTime(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars,
	int32 Beat, float BeatFraction)
{
	const FOnQuartzCommandEventBP EmptyOnQuartzCommandEventBP; 
	AttachedAudioComponent->PlayQuantized(GetWorld(),Clock, QuartzQuantizationBoundary, EmptyOnQuartzCommandEventBP);
}


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

// Called every frame
void UAudioCuePlayer::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

