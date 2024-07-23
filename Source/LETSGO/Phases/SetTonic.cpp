// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTonic.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "Logging/StructuredLog.h"
#include "Math/UnitConversion.h"

ASetTonic::ASetTonic(): Spawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Spawner = CreateDefaultSubobject<AAudioPlatformSpawner>(TEXT("Audio Platform Spawner"));
}

void ASetTonic::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("SetTonic BeginPlay complete"));

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
	const FTransform CameraForward = Spawner->GetCameraVectorForward();
	FVector RootLocation = CameraForward.GetTranslation();
	

	const int HalfLength = DivRoundClosest(NumPlatformsToSpawn, 2);
	const TArray<FLetsGoMusicNotes> PlatformNotes = GetRandomNotes(NumPlatformsToSpawn);

	// Spawn three Audio Platforms 
	for (int i = 0; i < NumPlatformsToSpawn; i++)
	{
		AAudioPlatform* SpawnedPlatform = Spawner->SpawnPlatform(CameraForward, PlatformNotes[i]);

		const int SidePosition = i - (NumPlatformsToSpawn / 2);
		const double YPos = SidePosition * OffsetAmountPerSpawnedPlatform;
		RootLocation.Y += YPos;
		RootLocation.Z = 1;
		SpawnedPlatform->AddActorLocalOffset(FVector(0, YPos, 0));
		
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
	Spawner->InitiateDestroy();

	Active = false;
}

void ASetTonic::Complete()
{
	OnPhaseComplete.Broadcast(this);

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
	
	Complete();
}

// Might could move this to ULetsGoMusicEngine
TArray<FLetsGoMusicNotes> ASetTonic::GetRandomNotes(int NumberOfNotes)
{
	TArray<FLetsGoMusicNotes> ToReturn = TArray<FLetsGoMusicNotes>();
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

	if (NumberOfNotes > Notes.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("GetRandomNotes called with NumberOfNotes > Number of posssible notes. Resizing to max"));
		NumberOfNotes = Notes.Num();
	}

	for (int i = 0; i < NumberOfNotes; i++)
	{
		const int Key = FMath::RandRange(0, (Notes.Num() - 1) );
		ToReturn.Add(Notes[Key]);
		Notes.RemoveAt(Key);	
	}
	
	return ToReturn;
}

int ASetTonic::DivRoundClosest(const int n, const int d)
{
	return ((n < 0) == (d < 0)) ? ((n + d/2)/d) : ((n - d/2)/d);
}
