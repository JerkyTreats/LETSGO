// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioPlatform.h"

UAudioPlatform::UAudioPlatform()
{
}

void UAudioPlatform::NotifyActorBeginOverlap(AActor* OtherActor)
{
	HandlePlatformTriggeredEvent();
}

void UAudioPlatform::HandlePlatformTriggeredEvent()
{
	OnAudioPlatformTriggered.Broadcast(Note);
}



