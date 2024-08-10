// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/AudioPlatform/APlatformAudioCuePlayer.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "AAudioPlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAudioPlatformTriggerDelegate, FLetsGoMusicNotes, Note);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAudioPlatformDestroyDelegate);

/**
 * 
 */
UCLASS(Blueprintable)
class LETSGO_API AAudioPlatform : public AActor
{
	GENERATED_BODY()

public:
	AAudioPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	FLetsGoMusicNotes Note;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO | AudioPlatform")
	FAudioPlatformTriggerDelegate OnAudioPlatformTriggered;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO | AudioPlatform")
	FAudioPlatformDestroyDelegate OnAudioPlatformDestroy;
	
	UPROPERTY(EditDefaultsOnly, Blueprintable)
	APlatformAudioCuePlayer* AudioCuePlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	float ActorDestroyDelay;
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;



public:
	UFUNCTION(BlueprintCallable)
	void SetAudioCuePlayer(APlatformAudioCuePlayer* PlayerToSet);

	UFUNCTION()
	void DestroyActor();

};
