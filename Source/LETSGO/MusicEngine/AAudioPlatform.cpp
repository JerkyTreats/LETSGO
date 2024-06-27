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

		FTimerHandle MemberTimerHandle;
		
		// Allow slight delay then destroy this platform
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AAudioPlatform::DestroyActor, ActorDestroyDelay, false);
	}
}

// MUST REARRANGE ORDER HERE
// REMOVE DESTROY FROM OVERLAP AND PLACE HERE
// WILL NEED TO UPDATE BLUEPRINT SPAWNER TO EXPLICITLY ORDER DESTROY OnAudioPlatformTriggered
void AAudioPlatform::DestroyActor()
{
	Destroy();
}


