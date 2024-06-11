// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTonic.h"

#include "Logging/StructuredLog.h"

void USetTonic::OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote)
{
	
}

void USetTonic::SetTonic(FLetsGoMusicNotes Note)
{
	
}

void USetTonic::Initialize()
{
}

void USetTonic::Activate()
{
	// Spawn three Audio Platforms 
	for (int i = 0; i <=3; i++)
	{
		AAudioPlatform* next = GetWorld()->SpawnActor<AAudioPlatform>(AAudioPlatform::StaticClass(), )
	}
}

void USetTonic::Deactivate()
{
}
