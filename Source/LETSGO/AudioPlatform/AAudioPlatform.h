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
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO")
	FAudioPlatformTriggerDelegate OnAudioPlatformTriggered;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO")
	FAudioPlatformDestroyDelegate OnAudioPlatformDestroy;

	UPROPERTY()
	APlatformAudioCuePlayer* AudioCuePlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LETSGO")
	TSubclassOf<APlatformAudioCuePlayer> AudioCuePlayerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	float ActorDestroyDelay;
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void DestroyActor();

};
