// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "Components/ActorComponent.h"
#include "LETSGO/Instruments/Instrument.h"
#include "LETSGO/Instruments/Cheese Keys/CheeseKeySoundCueMapping.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Sound/SoundCue.h"
#include "APlatformAudioCuePlayer.generated.h"


UCLASS(Blueprintable, ClassGroup=(LETSGO), meta=(BlueprintSpawnableComponent))
class LETSGO_API APlatformAudioCuePlayer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	APlatformAudioCuePlayer();
	
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	class AAudioPlatform* AudioPlatformReference;
	
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	FQuartzQuantizationBoundary QuartzQuantizationBoundary = {
		EQuartzCommandQuantization::Beat,
		1.0f,
		EQuarztQuantizationReference::BarRelative,
		true
	};;

	UPROPERTY()
	UAudioComponent* AttachedAudioComponent;

	UPROPERTY(VisibleAnywhere, Category = "LETSGO | State")  
	UQuartzClockHandle* Clock;

	//Instrument Data
	UPROPERTY()
	ACheeseKeySoundCueMapping* CheeseKeyData;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<ACheeseKeySoundCueMapping> CheeseKeyClass;

	UPROPERTY()
	AInstrument* Instrument;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	bool IsSoundPlaying = false;
	
	// Function to fire when the OnAudioPlatformTriggered Event is received
	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote);

	UFUNCTION()
	FInstrumentSchedule BuildInstrumentSchedule(TEnumAsByte<ELetsGoMusicNotes> ENote) const;
	
public:
	UFUNCTION(BlueprintCallable)
	void DestroyActor();

	UFUNCTION()
	void InitiateDestroy();
};
