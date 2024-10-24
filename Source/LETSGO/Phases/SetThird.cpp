﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SetThird.h"

#include "LETSGO/LETSGO.h"
#include "LETSGO/AudioPlatform/AAudioPlatformSpawner.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


class ALetsGoGameMode;
// Sets default values
ASetThird::ASetThird(): Spawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spawner = CreateDefaultSubobject<AAudioPlatformSpawner>(TEXT("Audio Platform Spawner"));
}

// Called when the game starts or when spawned
void ASetThird::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetThird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASetThird::Initialize()
{
	Spawner = GetWorld()->SpawnActor<AAudioPlatformSpawner>(AudioPlatformSpawnerClass);
	
}

void ASetThird::Activate()
{
	Active = true;

	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	const FLetsGoMusicNotes Tonic = GameMode->GetTonic();

	FLetsGoGeneratedScale Chromatic = FLetsGoGeneratedScale(Tonic, ULetsGoMusicEngine::Chromatic);

	const TArray<int> Intervals = ULetsGoMusicEngine::GetInterval(3);

	const TArray PlatformNotes = {
		Chromatic.Notes[Intervals[0]],
		Chromatic.Notes[Intervals[1]]
	};
	
	TArray<AAudioPlatform*> AudioPlatforms = Spawner->SpawnPlatforms(PlatformNotes);
	
	for (int i = 0; i < AudioPlatforms.Num(); i++)
	{
		AudioPlatforms[i]->OnAudioPlatformTriggered.AddUniqueDynamic(this, &ASetThird::SetThird);
	}
	
}

bool ASetThird::IsActivated()
{
	return Active;
}

void ASetThird::Deactivate()
{
	Active = false;
}

void ASetThird::Complete()
{
	Deactivate();
	
	Completed = true;
}

bool ASetThird::IsCompleted()
{
	return Completed;
}

void ASetThird::InitiateDestroy()
{
	Spawner->InitiateDestroy();
	Destroy();
}

void ASetThird::SetThird(FLetsGoMusicNotes Note)
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	const int Interval = GameMode->GetChromaticScale().Notes.IndexOfByPredicate([&](const FLetsGoMusicNotes& InNote)
	{
		return InNote.Note == Note.Note;
	});

	if (Interval == INDEX_NONE )
	{
		UE_LOG(LogLetsgo, Error, TEXT("GetThird could not find Predicate Note"))
		Complete();		
	}
	
	GameMode->SetInterval(Interval);
	Complete();
}

