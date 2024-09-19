// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"

#include "PedalPoint_MusicalStrategy.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AMusicComposer::AMusicComposer(): ComposerData(), CompositionStrategies()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMusicComposer::BeginPlay()
{
	Super::BeginPlay();

	IMusicCompositionStrategy* PedalPoint = NewObject<UPedalPoint_MusicalStrategy>();

	CompositionStrategies.Emplace(PedalPoint);
}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMusicComposer::Initialize()
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnMusicalStateUpdated.AddDynamic(this, &AMusicComposer::GenerateScale);

}

void AMusicComposer::GenerateScale()
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	FLetsGoMusicNotes Tonic = GameMode->GetTonic();
	FLetsGoMusicNotes Second = GameMode->GetSecond();
	FLetsGoMusicNotes Third = GameMode->GetThird();
	FLetsGoMusicNotes Fourth = GameMode->GetFourth();
	FLetsGoMusicNotes Fifth = GameMode->GetFifth();
	FLetsGoMusicNotes Sixth = GameMode->GetSixth();
	FLetsGoMusicNotes Seventh = GameMode->GetSeventh();

	Scale = FLetsGoGeneratedScale();
}

FInstrumentSchedule AMusicComposer::ComposeInstrumentSchedule()
{
	return FInstrumentSchedule();
}
