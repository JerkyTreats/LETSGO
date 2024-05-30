// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "Components/ActorComponent.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "UAudioCuePlayer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LETSGO_API UAudioCuePlayer : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAudioCuePlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite)
	class AAudioPlatform* AudioPlatformReference;

	UFUNCTION()
	void OnAudioPlatformTriggered(FLetsGoMusicNotes Note);

	UFUNCTION()
	void PlayNote(FLetsGoMusicNotes Note);

	UFUNCTION()
	void OnBar(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);

	// https://abovenoisestudios.com/blogeng/metasquartzverticalengp2
	/**
	 * @brief Function delegate. Triggers its functionality synced with the clock.
	 * @param EventType Use a switch on this enumeration to select "CommandOnQueued". 
	 * @param Name 
	 */
	UFUNCTION()
	void FPlayQuantizedDelegate(EQuartzCommandDelegateSubType EventType, FName Name);

	/** Used to bind the FPlayQuantizedDelegate in the class constructor. */
	FOnQuartzCommandEventBP PlayQuantizationDelegate;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, Category = "LETSGO | State")  
	UQuartzClockHandle* Clock;
};
