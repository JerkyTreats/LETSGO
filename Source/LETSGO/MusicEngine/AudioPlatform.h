// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "AudioPlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAudioPlatformTriggerDelegate, FLetsGoMusicNotes, Note);

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LETSGO_API UAudioPlatform : public UActorComponent
{
	GENERATED_BODY()

public:
	UAudioPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLetsGoMusicNotes Note;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO | AudioPlatform")
	FAudioPlatformTriggerDelegate OnAudioPlatformTriggered;

	
protected:

	// Called when the game starts or when spawned
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	UFUNCTION()
	void HandlePlatformTriggeredEvent();
};
