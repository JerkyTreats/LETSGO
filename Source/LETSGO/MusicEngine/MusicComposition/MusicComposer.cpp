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

	// Default Scale to C Major
	ComposerState->Initialize();
	
	InitializeStrategies();
	InitializeComposerData();
	
}

void AMusicComposer::InitializeComposerData()
{
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	// ADrumSoundCueMapping* SoundCueMapping =  GameMode->GetInstrumentData_Drums();
	
	/*
	FComposerData Snare = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Snare));
	FComposerData Kick = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Kick));
	FComposerData HiHatOpen = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::HiHatOpen));
	FComposerData HiHatClosed = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::HiHatClosed));
	FComposerData Clap = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Clap));
	*/

	FInstrumentData CheeseInstrumentData = ComposerState->CheeseKeySoundCueMapping->NoteData;

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
	MusicalStrategies = TArray<FMusicStrategyData>();

	MusicalStrategies.Emplace(FMusicStrategyData(
		NewObject<UStrategy_PedalPointComposition>(),
		0.0f,
		PedalPoint		
	));

}

FInstrumentScheduleData AMusicComposer::GenerateBars(FComposerData ComposerData, const int StartAtBar, const int TimesToRepeat)
{
	FMusicStrategyData ChosenStrategy = MusicalStrategies[0]; 
	for(int i = 0; i < MusicalStrategies.Num(); i++)
	{
		FMusicStrategyData CandidateStrategy = MusicalStrategies[i];
		const float Appropriateness = CandidateStrategy.Strategy->GetStrategyAppropriateness(
					ComposerData, ComposerState);
		if ( Appropriateness > ChosenStrategy.StrategyAppropriateness)
		{
			CandidateStrategy.StrategyAppropriateness = Appropriateness;
			ChosenStrategy = CandidateStrategy;
		}
	}

	/*
	if (ChosenStrategy.StrategyAppropriateness == 0.0f)
	{
		return FInstrumentScheduleData();
	}
	*/

	FInstrumentScheduleData ScheduleData = FInstrumentScheduleData( FInstrumentSchedule(), StartAtBar, TimesToRepeat);

	FInstrumentSchedule InstrumentSchedule = ChosenStrategy.Strategy->Apply(ComposerData, ScheduleData);

	ScheduleData.InstrumentSchedule = InstrumentSchedule;
	ScheduleData.StrategyData = ChosenStrategy;

	return ScheduleData;
}

void AMusicComposer::GenerateScale()
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	ComposerState->Scale = GameMode->GetChromaticScale();

	// Allow pentatonic on Tonic set
	ComposerState->AllowableNoteIndices = { 0, 2, 7, 9 };
}

void AMusicComposer::UpdateAllowableNoteIndices(int Interval)
{
	ComposerState->AllowableNoteIndices.AddUnique(Interval);
}

//Every bar, the Composer:

// Updates Strategy Appropriateness

void AMusicComposer::CheckAndGenerateBars(const int32 NumBars)
{
	int32 BarsDefined = 0;

	// Does this ComposerData need more bars defined? 
	for (int i = 0; i < ComposerState->ComposerDataObjects.Num(); i++ )
	{
		FComposerData ComposerData = ComposerState->ComposerDataObjects[i];

		// Peer into each ComposerDatas InstrumentSchedules to determine how many bars we have
		for(int ScheduleIndex = 0; ScheduleIndex < ComposerData.ScheduleData.Num(); ScheduleIndex++)
		{
			const FInstrumentScheduleData ScheduleData = ComposerData.ScheduleData[ScheduleIndex];
			if(const int32 BarSchedule = ScheduleData.StartAtBar * ScheduleData.TimesToRepeat; BarSchedule > BarsDefined)
			{
				BarsDefined = BarSchedule;
			}
		}

		// Define bars for this instrument
		if (BarsDefined - NumBars < ComposerState->BarCreationThreshold)
		{
			//TODO Times to Repeat magic number
			FInstrumentScheduleData NewSchedule = GenerateBars(ComposerData, NumBars + 1, 2);

			if (NewSchedule.IsValid)
			{
				ComposerState->ComposerDataObjects[i].ScheduleData.Emplace(NewSchedule);
			}
		}
	}
}

// - Checks the set of ComposerData’s
// - If there are no objects, trigger some CreationStrategy
// - If there are objects, check if there are more than 2 bars worth of data for those instruments to play
// - If not, trigger an UpdateStrategy
void AMusicComposer::OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat,
	float BeatFraction)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Bar %i"), NumBars));

	int StartAtBar = NumBars;

	if (! Started)
	{
		StartAtBar += 2;
		Started = true;
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Started")));
	}
	
	CheckAndGenerateBars(StartAtBar);

	for (int i = 0; i < ComposerState->ComposerDataObjects.Num(); i++)
	{
		for (int x = 0; x < ComposerState->ComposerDataObjects[i].ScheduleData.Num(); x++)
		{
			FInstrumentScheduleData ScheduleData = ComposerState->ComposerDataObjects[i].ScheduleData[x];

			if (ScheduleData.StartAtBar == NumBars)
			{
				AInstrument* Instrument = GetWorld()->SpawnActor<AInstrument>(InstrumentClass);
				Instrument->Initialize(ScheduleData.InstrumentSchedule);
				Instrument->StartPlaying();
			}
		}
	}
}
