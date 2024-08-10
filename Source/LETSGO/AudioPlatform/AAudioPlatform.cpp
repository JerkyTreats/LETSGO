// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioPlatform.h"
#include "GameFramework/Character.h"

AAudioPlatform::AAudioPlatform()
{
	AudioCuePlayer = CreateDefaultSubobject<APlatformAudioCuePlayer>(TEXT("Audio Cue Player"));
}

void AAudioPlatform::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	// Only broadcast if it's a player character
	if (Cast<ACharacter>(OtherActor))
	{
		OnAudioPlatformTriggered.Broadcast(Note);
	}
}

// MUST REARRANGE ORDER HERE
// REMOVE DESTROY FROM OVERLAP AND PLACE HERE
// WILL NEED TO UPDATE BLUEPRINT SPAWNER TO EXPLICITLY ORDER DESTROY OnAudioPlatformTriggered
void AAudioPlatform::DestroyActor()
{
	OnAudioPlatformDestroy.Broadcast();
	AudioCuePlayer->InitiateDestroy();
	Destroy();
}

void AAudioPlatform::SetAudioCuePlayer(APlatformAudioCuePlayer* PlayerToSet)
{
	AudioCuePlayer = PlayerToSet;
}


