// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTonic.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "Logging/StructuredLog.h"

USetTonic::USetTonic()
{
	Spawner =  CreateDefaultSubobject<AAudioPlatformSpawner>(TEXT("Set Tonic Audio Platform Spawner"));
}

void USetTonic::OnAudioPlatformTriggered(FLetsGoMusicNotes IncomingNote)
{
	
}



void USetTonic::Initialize()
{
}

// Might could move this to ULetsGoMusicEngine
FLetsGoMusicNotes USetTonic::GetRandomNote()
{
	TMap<int, FLetsGoMusicNotes> Map;
	Map.Add(0, FLetsGoMusicNotes(C));
	Map.Add(0, FLetsGoMusicNotes(CSharp));
	Map.Add(0, FLetsGoMusicNotes(D));
	Map.Add(0, FLetsGoMusicNotes(EFlat));
	Map.Add(0, FLetsGoMusicNotes(E));
	Map.Add(0, FLetsGoMusicNotes(F));
	Map.Add(0, FLetsGoMusicNotes(FSharp));
	Map.Add(0, FLetsGoMusicNotes(G));
	Map.Add(0, FLetsGoMusicNotes(AFlat));
	Map.Add(0, FLetsGoMusicNotes(A));
	Map.Add(0, FLetsGoMusicNotes(BFlat));
	Map.Add(0, FLetsGoMusicNotes(B));

	const int Key = FMath::RandRange(0, Map.Num());

	return Map[Key];
}

void USetTonic::Activate()
{
	FTransform CameraForward = Spawner->GetCameraVectorForward();
	FVector RootLocation = CameraForward.GetTranslation();
	const FActorSpawnParameters SpawnInfo;
	

	const int HalfLength = NumPlatformsToSpawn / 2;
	
	// Spawn three Audio Platforms 
	for (int i = 0; i <=NumPlatformsToSpawn; i++)
	{
		const int YPos = (i - HalfLength) * OffsetAmountPerSpawnedPlatform;

		RootLocation.Y += YPos;
		CameraForward.SetTranslation(RootLocation);
		const FLetsGoMusicNotes PlatformNote = GetRandomNote();
		
		AAudioPlatform* SpawnedPlatform = Spawner->SpawnPlatform(CameraForward, PlatformNote);
		SpawnedPlatform->OnAudioPlatformTriggered.AddDynamic(this, &USetTonic::SetTonic);
	}
	
}

void USetTonic::Deactivate()
{
}

void USetTonic::SetTonic(FLetsGoMusicNotes Note)
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetTonic(Note);

	Spawner->DestroyAllPlatforms();
}