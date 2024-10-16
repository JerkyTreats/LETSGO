// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposerState.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AMusicComposerState::AMusicComposerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheeseKeySoundCueMapping = CreateDefaultSubobject<ACheeseKeySoundCueMapping>(TEXT("Cheese"));
	DrumsSoundCueMapping = CreateDefaultSubobject<ADrumSoundCueMapping>(TEXT("Drums"));

}

// Called when the game starts or when spawned
void AMusicComposerState::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMusicComposerState::BeginDestroy()
{
	
	Super::BeginDestroy();

}

// Called every frame
void AMusicComposerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMusicComposerState::Initialize()
{
	Scale = ULetsGoMusicEngine::GenerateScale(ULetsGoMusicEngine::Chromatic, FLetsGoMusicNotes(C));
	AllowableNoteIndices = TArray<int>();
	
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	CheeseKeySoundCueMapping = GameMode->GetInstrumentData_CheeseKey();
	DrumsSoundCueMapping = GameMode->GetInstrumentData_Drums();
	
}

