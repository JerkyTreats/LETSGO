// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"
#include "Strategy_PedalPointComposition.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AMusicComposer::AMusicComposer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnBeatQuantizationDelegate.BindUFunction(this, "OnQuantizationBoundaryTriggered");
}

// Called when the game starts or when spawned
void AMusicComposer::BeginPlay()
{
	Super::BeginPlay();

	ComposerState = GetWorld()->SpawnActor<AMusicComposerState>(ComposerStateClass);
}

void AMusicComposer::BeginDestroy()
{
	/*if (Clock)
		Clock->StopClock(GetWorld(), true, Clock);*/

	Super::BeginDestroy();
}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ComposerState->CurrentBar > LastProcessedBar)
	{
		CheckAndGenerateBars();
		LastProcessedBar = ComposerState->CurrentBar;
	}
}


void AMusicComposer::GenerateScale()
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	ComposerState->Scale = GameMode->GetChromaticScale();

	// Allow pentatonic on Tonic set
	ComposerState->AllowableNoteIndices = { 0, 2, 7, 9 };

	ComposerState->IsTonicSet = true;
}

void AMusicComposer::UpdateAllowableNoteIndices(int Interval)
{
	ComposerState->AllowableNoteIndices.AddUnique(Interval);
}

// Setup a custom tick for composition, based on MainClock bar
void AMusicComposer::Initialize()
{
	const UWorld* World = GetWorld();
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(World->GetAuthGameMode());
	GameMode->OnTonicSet.AddDynamic(this, &AMusicComposer::GenerateScale);
	GameMode->OnIntervalSet.AddUniqueDynamic(this, &AMusicComposer::UpdateAllowableNoteIndices);

	/*
	const AClockSettings* ClockSettings = GameMode->GetClockSettings();
	Clock = ClockSettings->GetNewClock(FName(TEXT("ComposerClock")));
	Clock->StartClock(World, Clock);
	Clock->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Bar, OnBeatQuantizationDelegate, Clock);
	*/

	ComposerState->Initialize();
	
	InitializeStrategies();
	InitializeComposerData();
	
}

void AMusicComposer::InitializeComposerData()
{
	
	/*
	FComposerData Snare = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Snare));
	FComposerData Kick = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Kick));
	FComposerData HiHatOpen = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::HiHatOpen));
	FComposerData HiHatClosed = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::HiHatClosed));
	FComposerData Clap = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Clap));
	*/

	const FInstrumentData CheeseInstrumentData = ComposerState->CheeseKeySoundCueMapping->NoteData;

	FComposerData Bass = FComposerData(EInstrumentRoles::Bass, CheeseInstrumentData);
	Bass.OctaveMin = 2;
	Bass.OctaveMax = 2;
	
	FComposerData Tenor = FComposerData(EInstrumentRoles::Tenor, CheeseInstrumentData);
	Tenor.OctaveMin = 3;
	Tenor.OctaveMax = 3;
	
	FComposerData Alto = FComposerData(EInstrumentRoles::Alto, CheeseInstrumentData);
	Alto.OctaveMin = 4;
	Alto.OctaveMax = 4;
	
	FComposerData Soprano = FComposerData(EInstrumentRoles::Soprano, CheeseInstrumentData);
	Soprano.OctaveMin = 5;
	Soprano.OctaveMax = 5;

	ComposerState->ComposerDataObjects = TArray<FComposerData>
	{
		/*Snare,
		Kick,
		HiHatClosed,
		HiHatOpen,
		Clap,*/

		Bass,
		Tenor,
		Alto,
		Soprano
	};
}

void AMusicComposer::InitializeStrategies()
{
	MusicalStrategies = {
		NewObject<UStrategy_PedalPointComposition>()
	};
}

IMusicStrategy* AMusicComposer::ChooseMusicalStrategy(const FComposerData& ComposerData, float& AppropriatenessOut)
{
	IMusicStrategy* ChosenStrategy = MusicalStrategies[0];

	for(int i = 0; i < MusicalStrategies.Num(); i++)
	{
		IMusicStrategy* CandidateStrategy = MusicalStrategies[i];
		const float CandidateAppropriateness = CandidateStrategy->GetStrategyAppropriateness(
			ComposerData, ComposerState);
		if ( CandidateAppropriateness > AppropriatenessOut)
		{
			AppropriatenessOut = CandidateAppropriateness;
			ChosenStrategy = CandidateStrategy;
		}
	}

	return ChosenStrategy;
}

FInstrumentSchedule AMusicComposer::GenerateBars(FComposerData& ComposerData, IMusicStrategy* ChosenStrategy, const int StartAtBar, const int TimesToRepeat)
{
	FPerBarSchedule Bar = ChosenStrategy->GenerateBar(ComposerData, ComposerState);
	FInstrumentSchedule InstrumentSchedule = FInstrumentSchedule(EQuartzCommandQuantization::QuarterNote, Bar, TimesToRepeat, StartAtBar);

	return InstrumentSchedule;
}

void AMusicComposer::CheckAndGenerateBars()
{
	int32 BarsDefined = 0;

	// Does this ComposerData need more bars defined? 
	for (int i = 0; i < ComposerState->ComposerDataObjects.Num(); i++ )
	{
		FComposerData ComposerData = ComposerState->ComposerDataObjects[i];

		// Peer into each ComposerDatas InstrumentSchedules to determine how many bars we have
		for(int ScheduleIndex = 0; ScheduleIndex < ComposerData.ScheduleData.Num(); ScheduleIndex++)
		{
			const FInstrumentSchedule ScheduleData = ComposerData.ScheduleData[ScheduleIndex];
			if(const int32 BarSchedule = ScheduleData.StartAtBar * ScheduleData.BeatSchedule.Num(); BarSchedule > BarsDefined)
			{
				BarsDefined = BarSchedule;
			}
		}

		// Define bars for this instrument
		if (BarsDefined - ComposerState->CurrentBar < ComposerState->BarCreationThreshold)
		{
			float StrategyAppropriateness = 0.0f;
			IMusicStrategy* ChosenStrategy = ChooseMusicalStrategy(ComposerData, StrategyAppropriateness);

			if (StrategyAppropriateness < ComposerState->MusicalStrategyAppropriatenessThreshold)
				return;
			
			//TODO Times to Repeat magic number
			FInstrumentSchedule NewSchedule = GenerateBars(ComposerData, ChosenStrategy, BarsDefined + 1, 2);
			ComposerState->ComposerDataObjects[i].ScheduleData.Emplace(NewSchedule);
		}
	}
}

/*
// - Checks the set of ComposerData’s
// - If there are no objects, trigger some CreationStrategy
// - If there are objects, check if there are more than 2 bars worth of data for those instruments to play
// - If not, trigger an UpdateStrategy
void AMusicComposer::OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat,
	float BeatFraction)
{
	if (! ComposerState->IsTonicSet)
		return;
	
	int StartAtBar = ComposerState->CurrentBar;

	if (! Started)
	{
		StartAtBar += 2;
		Started = true;
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Started")));
	}
	
	CheckAndGenerateBars(StartAtBar);
}
*/
