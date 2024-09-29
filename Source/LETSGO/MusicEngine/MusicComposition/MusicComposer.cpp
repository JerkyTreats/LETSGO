// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"

#include "Strategy_PedalPointComposition.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AMusicComposer::AMusicComposer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnBeatQuantizationDelegate.BindUFunction(this, "OnBeat");
}

// Called when the game starts or when spawned
void AMusicComposer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Setup a custom tick for composition, based on MainClock bar
void AMusicComposer::Initialize()
{
	const UWorld* World = GetWorld();
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(World->GetAuthGameMode());
	GameMode->OnMusicalStateUpdated.AddDynamic(this, &AMusicComposer::GenerateScale);

	const AClockSettings* ClockSettings = GameMode->GetClockSettings();
	UQuartzClockHandle* MainClock = ClockSettings->MainClock;
	MainClock->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Bar, OnBeatQuantizationDelegate, MainClock);

	InitializeStrategies();
	
}

void AMusicComposer::InitializeStrategies()
{
	MusicalStrategies = TArray<FMusicalStrategy>();

	IMusicCompositionStrategy* PedalPoint = NewObject<UStrategy_PedalPointComposition>();


	TArray<IMusicCompositionStrategy*> StrategyInterfaces = {
		PedalPoint,
	};
	

	for (IMusicCompositionStrategy* StrategyInterface : StrategyInterfaces)
	{
		FMusicalStrategy Strategy = FMusicalStrategy();
		Strategy.Strategy = StrategyInterface;

		MusicalStrategies.Emplace(Strategy);
	}
}

void AMusicComposer::GenerateScale()
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	const FLetsGoMusicNotes Tonic = GameMode->GetTonic();
	const FLetsGoMusicNotes Second = GameMode->GetSecond();
	const FLetsGoMusicNotes Third = GameMode->GetThird();
	const FLetsGoMusicNotes Fourth = GameMode->GetFourth();
	const FLetsGoMusicNotes Fifth = GameMode->GetFifth();
	const FLetsGoMusicNotes Sixth = GameMode->GetSixth();
	const FLetsGoMusicNotes Seventh = GameMode->GetSeventh();

	const TArray<FLetsGoMusicNotes> Notes {
		Tonic,
		Second,
		Third,
		Fourth,
		Fifth,
		Sixth,
		Seventh
	};
	
	FLetsGoGeneratedScale NewScale = FLetsGoGeneratedScale();
	NewScale.Notes = Notes;
	NewScale.Tonic = Tonic;
	NewScale.IsValid = true;

	Scale = NewScale;
}

void AMusicComposer::ChooseMusicalStrategy()
{
}

FInstrumentSchedule AMusicComposer::ComposeInstrumentSchedule()
{
	return FInstrumentSchedule();
}

//Every bar, the Composer:
// - Checks the set of ComposerData’s
// - If there are no objects, trigger some CreationStrategy
// - If there are objects, check if there are more than 2 bars worth of data for those instruments to play
// - If not, trigger an UpdateStrategy
void AMusicComposer::OnBeat(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat,
	float BeatFraction)
{
	for (int i = 0; i < ComposerDataObjects.Num(); i++)
	{
		// Check 
	}
}
