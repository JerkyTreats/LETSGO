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

	ComposerDataObjects = MakeShared<TArray<FComposerData>>();

	SongSections = FSongSections::InitializeSongSections();

	GenerateMusicalIdea();
}

void AMusicComposerState::GenerateMusicalIdea()
{
	/*
	Common chord patterns. Not currently handling multi-bar patterns
	1-5-6-4 
	1-4-5-4
	2-5-1
	1-1-1-1, 4-4-1-1, 5-4-1-1
	1-6-4-5
	1-5-6-3, 4-1-4-5
	*/

	int Pick = FMath::RandRange(1, 5);
	switch (Pick)
	{
	case 1:
		{
			MusicalIdeaSeed = { 2, 5, 1, 1 };
			break;
		}
	case 2:
		{
			MusicalIdeaSeed = { 1, 5, 6, 4 }; 
			break;
		}
	case 3:
		{
			MusicalIdeaSeed = { 1, 4, 5, 4 }; 
			break;
		}
	case 4:
		{
			MusicalIdeaSeed = { 1, 6, 4, 5 }; 
			break;
		}
	case 5:
		{
			MusicalIdeaSeed = { 1, 5, 6, 3 }; 
			break;
		}
	default: MusicalIdeaSeed = { 1, 1, 1, 1};
	}
}

