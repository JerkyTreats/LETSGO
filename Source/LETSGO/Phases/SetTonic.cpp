// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTonic.h"

#include "LETSGO/MusicEngine/AAudioPlatformSpawner.h"
#include "Logging/StructuredLog.h"

USetTonic::USetTonic()
{
	Spawner =  CreateDefaultSubobject<AAudioPlatformSpawner>(TEXT("Set Tonic Audio Platform Spawner"));
}

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
	FTransform CameraForward = Spawner->GetCameraVectorForward();
	const FVector RootLocation = CameraForward.GetTranslation();
	const FRotator RootRotation = CameraForward.Rotator();
	const FActorSpawnParameters SpawnInfo;
	
	// Add prop for number of platforms to spawn
	// Similar to logic for spawning letter particle systems, define offset each platform from the RootLocation
	// Spawn each platform using the OffsetLocation
	
	// // Spawn three Audio Platforms 
	// for (int i = 0; i <=3; i++)
	// {
	// 	AAudioPlatform* next = GetWorld()->SpawnActor<AAudioPlatform>(AAudioPlatform::StaticClass(), );
	// }
}

void USetTonic::Deactivate()
{
}
