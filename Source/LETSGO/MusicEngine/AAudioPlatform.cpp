// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioPlatform.h"
#include "GameFramework/Character.h"

AAudioPlatform::AAudioPlatform()
{
}

void AAudioPlatform::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	// Only broadcast if it's a player character
	if (Cast<ACharacter>(OtherActor))
	{
		OnAudioPlatformTriggered.Broadcast(Note);
	}
}

/*void AAudioPlatform::HandlePlatformTriggeredEvent() const
{
	
}*/

