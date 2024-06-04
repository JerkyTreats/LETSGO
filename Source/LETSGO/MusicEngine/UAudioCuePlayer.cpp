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
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::A), A2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::AFlat), AFlat2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::BFlat), BFlat2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::B), B_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::C), C3_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::CSharp), CSharp3_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::D), D2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::EFlat), EFlat2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::E), E2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::F), F2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::FSharp), FSharp2_Music_Note);
	NoteCueMap.Add(FLetsGoMusicNotes(ELetsGoMusicNotes::G), G2_Music_Note);
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
	
	// Clock->SubscribeToQuantizationEvent(GetWorld(), EQuartzCommandQuantization::Beat, ExecuteInClockTimeDelegate, Clock);

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

void UAudioCuePlayer::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote)
{
	Note = IncomingNote;
	
	USoundCue* NoteToPlay = NoteCueMap.FindRef(Note);
	if(NoteToPlay == nullptr)
	{
		// TODO Build Custom Logging Section
		UE_LOGFMT(LogTemp, Error, "Note {0} does not exist in AudioCuePlayer::NoteCueMap", Note);
		return;
	}

	AttachedAudioComponent->SetSound(NoteToPlay);
	
	FExecuteInClockTime("", EQuartzCommandQuantization::None, 0, 0, 0);
	
}

void UAudioCuePlayer::FExecuteInClockTime(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars,
	int32 Beat, float BeatFraction)
{
	const FOnQuartzCommandEventBP EmptyOnQuartzCommandEventBP; 
	AttachedAudioComponent->PlayQuantized(GetWorld(),Clock, QuartzQuantizationBoundary, EmptyOnQuartzCommandEventBP);
}


// Called every frame
void UAudioCuePlayer::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

