// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAudioCuePlayer.h"
#include "ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "AAudioPlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAudioPlatformTriggerDelegate, FLetsGoMusicNotes, Note);

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

	UPROPERTY(EditDefaultsOnly, Blueprintable)
	AAudioCuePlayer* AudioCuePlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	float ActorDestroyDelay;
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void DestroyActor();

};
