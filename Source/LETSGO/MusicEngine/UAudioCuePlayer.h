// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "Components/ActorComponent.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Sound/SoundCue.h"
#include "UAudioCuePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReadyForCleanUpDelegate);


// See https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
UCLASS(Blueprintable, ClassGroup=(LETSGO), meta=(BlueprintSpawnableComponent))
class LETSGO_API UAudioCuePlayer : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAudioCuePlayer();
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO")
	FReadyForCleanUpDelegate ReadyForCleanUp;

	// Reference to the AudioPlatform
	// Required to Bind to the OnAudioPlatformTriggered Event
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	class AAudioPlatform* AudioPlatformReference;

	UPROPERTY(BlueprintReadWrite)
	FQuartzQuantizationBoundary QuartzQuantizationBoundary;
	
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

	UPROPERTY()
	UAudioComponent* AttachedAudioComponent;

	UPROPERTY(VisibleAnywhere, Category = "LETSGO | State")  
	UQuartzClockHandle* Clock;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Required to subscribe to Clock events 
	FOnQuartzMetronomeEventBP ExecuteInClockTimeDelegate;

	UFUNCTION()
	USoundCue* GetSoundCue(TEnumAsByte<ELetsGoMusicNotes> ENote) const;
	
	UFUNCTION()
	void OnAudioCueFinished();
	
	// Function to fire when the OnAudioPlatformTriggered Event is received
	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote);
	
public:
	// Called every frame
	virtual auto TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) -> void override;
	
	UFUNCTION()
	void Initialize(AAudioPlatform* AudioPlatform, const FQuartzQuantizationBoundary& Boundary);
	
};
