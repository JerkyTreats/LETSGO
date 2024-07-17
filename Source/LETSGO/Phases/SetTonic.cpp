// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTonic.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "Logging/StructuredLog.h"

USetTonic::USetTonic(): Spawner(nullptr)
{
}

void USetTonic::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote) 
{
	SetTonic(IncomingNote);
	Deactivate();
}


void USetTonic::Initialize(UWorld* World)
{
	Spawner = World->SpawnActor<AAudioPlatformSpawner>();
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
		RootLocation.Z = 1;
		CameraForward.SetTranslation(RootLocation);
		const FLetsGoMusicNotes PlatformNote = GetRandomNote();
		
		AAudioPlatform* SpawnedPlatform = Spawner->SpawnPlatform(CameraForward, PlatformNote);
		SpawnedPlatform->OnAudioPlatformTriggered.AddDynamic(this, &USetTonic::SetTonic);
	}
	
	Active = true;
}

bool USetTonic::IsActivated()
{
	return Active;
}

void USetTonic::Deactivate()
{
	OnPhaseComplete.Broadcast(this);

	Spawner->DestroyActor();

	Active = false;
}

void USetTonic::Complete()
{
	Deactivate();
	Completed = true;
}

bool USetTonic::IsCompleted()
{
	return Completed;
}

void USetTonic::SetTonic(FLetsGoMusicNotes Note)
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetTonic(Note);
}

// Might could move this to ULetsGoMusicEngine
FLetsGoMusicNotes USetTonic::GetRandomNote()
{
	TArray<FLetsGoMusicNotes> Notes = {
		FLetsGoMusicNotes(C),
		FLetsGoMusicNotes(CSharp),
		FLetsGoMusicNotes(D),
		FLetsGoMusicNotes(EFlat),
		FLetsGoMusicNotes(E),
		FLetsGoMusicNotes(FSharp),
		FLetsGoMusicNotes(G),
		FLetsGoMusicNotes(AFlat),
		FLetsGoMusicNotes(A),
		FLetsGoMusicNotes(BFlat),
		FLetsGoMusicNotes(B)
	};

	const int Key = FMath::RandRange(0, (Notes.Num() - 1) );

	return Notes[Key];
}
