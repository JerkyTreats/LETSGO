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

FLetsGoMusicNotes USetTonic::GetRandomNote()
{
	TMap<int, FLetsGoMusicNotes> Map = FMusicNoteMap.Map;
	FMath::RandRange(0, );
}

void USetTonic::Activate()
{
	FTransform CameraForward = Spawner->GetCameraVectorForward();
	FVector RootLocation = CameraForward.GetTranslation();
	const FRotator RootRotation = CameraForward.Rotator();
	const FActorSpawnParameters SpawnInfo;
	
	// Add prop for number of platforms to spawn
	// Similar to logic for spawning letter particle systems, define offset each platform from the RootLocation
	// Spawn each platform using the OffsetLocation

	float OffsetAmountPerPlatform = 40.0f;
	int NumPlatformsToSpawn = 3;
	int HalfLength = NumPlatformsToSpawn / 2;
	
	// Spawn three Audio Platforms 
	for (int i = 0; i <=NumPlatformsToSpawn; i++)
	{
		int YPos = (i - HalfLength) * OffsetAmountPerPlatform;

		RootLocation.Y += YPos;
		CameraForward.SetTranslation(RootLocation);
		FLetsGoMusicNotes PlatformNote = GetRandomNote();
		Spawner->SpawnPlatform(CameraForward, );
	}
	
}

void USetTonic::Deactivate()
{
}
