// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "Components/ActorComponent.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Sound/SoundCue.h"
#include "AAudioCuePlayer.generated.h"


// See https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
UCLASS(Blueprintable, ClassGroup=(LETSGO), meta=(BlueprintSpawnableComponent))
class LETSGO_API AAudioCuePlayer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	AAudioCuePlayer();

	// This is messy until I find a better solution
	// Set references to the note cues
	// The actual values are attached in AudioPlatform_BP in the Add Audio Cue Player node
	UPROPERTY(EditDefaultsOnly)
	USoundCue* A2_Music_Note;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* AFlat2_Music_Note;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* BFlat2_Music_Note;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* B_Music_Note;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* C3_Music_Note;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* CSharp3_Music_Note;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* D2_Music_Note;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* EFlat2_Music_Note;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* E2_Music_Note;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* F2_Music_Note;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* FSharp2_Music_Note;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* G2_Music_Note;

	UPROPERTY()
	TMap<TEnumAsByte<ELetsGoMusicNotes>, USoundCue*> NoteCueMap;
	
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	FQuartzQuantizationBoundary QuartzQuantizationBoundary;

	UPROPERTY()
	UAudioComponent* AttachedAudioComponent;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Reference to the AudioPlatform
	// Required to Bind to the OnAudioPlatformTriggered Event
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	class AAudioPlatform* AudioPlatformReference;

	// Function to fire when the OnAudioPlatformTriggered Event is received
	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote);
	
	// Required to subscribe to Clock events 
	FOnQuartzMetronomeEventBP ExecuteInClockTimeDelegate;

	UFUNCTION()
	USoundCue* GetSoundCue(TEnumAsByte<ELetsGoMusicNotes> ENote) const;
	
public:
	UPROPERTY(VisibleAnywhere, Category = "LETSGO | State")  
	UQuartzClockHandle* Clock;
};
