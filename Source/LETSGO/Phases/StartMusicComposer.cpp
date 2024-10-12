// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMusicComposer.h"

#include "LETSGO/MusicEngine/MusicComposition/MusicComposer.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AStartMusicComposer::AStartMusicComposer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStartMusicComposer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStartMusicComposer::Initialize()
{
	AMusicComposer* MusicComposer = GetWorld()->SpawnActor<AMusicComposer>(MusicComposerClass);
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Composer = MusicComposer;
	GameMode->SetMusicComposer(MusicComposer);
}

void AStartMusicComposer::Activate()
{
	Composer->Initialize();

	Completed = true;
}

bool AStartMusicComposer::IsActivated()
{
	return Active;
}

void AStartMusicComposer::Deactivate()
{
}

void AStartMusicComposer::Complete()
{
}

bool AStartMusicComposer::IsCompleted()
{
	return Completed;
}

void AStartMusicComposer::InitiateDestroy()
{
}

