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

void AAudioPlatform::BeginPlay()
{
	Super::BeginPlay();

	AudioCuePlayer = GetWorld()->SpawnActorDeferred<APlatformAudioCuePlayer>(AudioCuePlayerClass, FTransform());
	AudioCuePlayer-> AudioPlatformReference = this;
	AudioCuePlayer->FinishSpawning(FTransform());
}

void AAudioPlatform::DestroyActor()
{
	OnAudioPlatformDestroy.Broadcast();
	AudioCuePlayer->InitiateDestroy();
	Destroy();
}


