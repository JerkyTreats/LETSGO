// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTonic.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "Logging/StructuredLog.h"

ASetTonic::ASetTonic(): Spawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Spawner = CreateDefaultSubobject<AAudioPlatformSpawner>(TEXT("Audio Platform Spawner"));
}

void ASetTonic::BeginPlay()
{
	Super::BeginPlay();
}

void ASetTonic::OnAudioPlatformTriggered(const FLetsGoMusicNotes IncomingNote) 
{
	SetTonic(IncomingNote);
	Deactivate();
}


void ASetTonic::Initialize()
{
	Spawner = GetWorld()->SpawnActor<AAudioPlatformSpawner>(AudioPlatformSpawnerClass);
}

void ASetTonic::Activate()
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
		SpawnedPlatform->OnAudioPlatformTriggered.AddDynamic(this, &ASetTonic::SetTonic);
	}
	
	Active = true;
}

bool ASetTonic::IsActivated()
{
	return Active;
}

void ASetTonic::Deactivate()
{
	OnPhaseComplete.Broadcast(this);

	Spawner->DestroyActor();

	Active = false;
}

void ASetTonic::Complete()
{
	Deactivate();
	Completed = true;
}

bool ASetTonic::IsCompleted()
{
	return Completed;
}

void ASetTonic::SetTonic(FLetsGoMusicNotes Note)
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetTonic(Note);
}

// Might could move this to ULetsGoMusicEngine
FLetsGoMusicNotes ASetTonic::GetRandomNote()
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
