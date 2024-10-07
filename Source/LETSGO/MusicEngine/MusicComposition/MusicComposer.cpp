// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"

#include "MusicStrategyData.h"
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
	InitializeComposerData();
	
}

void AMusicComposer::InitializeComposerData()
{
	ADrumSoundCueMapping* SoundCueMapping = GetWorld()->SpawnActor<ADrumSoundCueMapping>(ADrumSoundCueMappingClass);
	
	FComposerData Snare = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Snare));
	FComposerData Kick = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Kick));
	FComposerData HiHatOpen = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::HiHatOpen));
	FComposerData HiHatClosed = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::HiHatClosed));
	FComposerData Clap = FComposerData(EInstrumentRoles::Snare,SoundCueMapping->GetInstrumentData(EInstrumentRoles::Clap));

	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	ACheeseKeySoundCueMapping* CheeseKeySoundCueMapping = GameMode->GetInstrumentData_CheeseKey();
	FInstrumentData CheeseInstrumentData = CheeseKeySoundCueMapping->NoteData;

	FComposerData Bass = FComposerData(EInstrumentRoles::Bass, CheeseInstrumentData);
	Bass.OctaveMax = 1;
	
	FComposerData Tenor = FComposerData(EInstrumentRoles::Bass, CheeseInstrumentData);
	Tenor.OctaveMin = 2;
	Tenor.OctaveMax = 3;
	
	FComposerData Alto = FComposerData(EInstrumentRoles::Bass, CheeseInstrumentData);
	Alto.OctaveMin = 3;
	Alto.OctaveMax = 4;
	
	FComposerData Soprano = FComposerData(EInstrumentRoles::Bass, CheeseInstrumentData);
	Soprano.OctaveMin = 4;
	Soprano.OctaveMax = 5;

	ComposerDataObjects = TArray<FComposerData>
	{
		Snare,
		Kick,
		HiHatClosed,
		HiHatOpen,
		Clap,

		Bass,
		Tenor,
		Alto,
		Soprano
	};
}

void AMusicComposer::InitializeStrategies()
{
	MusicalStrategies = TArray<FMusicStrategyData>();

	TArray<IMusicStrategy*> StrategyInterfaces = {
		NewObject<UStrategy_PedalPointComposition>(),
	};
	
	for (IMusicStrategy* StrategyInterface : StrategyInterfaces)
	{
		FMusicStrategyData Strategy = FMusicStrategyData();
		Strategy.Strategy = StrategyInterface;

		MusicalStrategies.Emplace(Strategy);
	}
}

FInstrumentScheduleData AMusicComposer::GenerateBars(FComposerData ComposerData, const int StartAtBar, const int TimesToRepeat)
{
	FMusicStrategyData ChosenStrategy = MusicalStrategies[0]; 
	for(int i = 0; i < MusicalStrategies.Num(); i++)
	{
		const FMusicStrategyData CandidateStrategy = MusicalStrategies[i];

		if (const float Appropriateness = CandidateStrategy.Strategy->GetStrategyAppropriateness(
			ComposerData, ComposerDataObjects, Scale); Appropriateness > ChosenStrategy.StrategyAppropriateness)
		{
			ChosenStrategy = CandidateStrategy;
		}
	}

	ChosenStrategy.GenerateInstrumentInputs(ComposerDataObjects);

	FInstrumentSchedule InstrumentSchedule = ChosenStrategy.Strategy->Apply(ComposerData);

	FInstrumentScheduleData ScheduleData = FInstrumentScheduleData(InstrumentSchedule, StartAtBar, TimesToRepeat);

	return ScheduleData;
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

//Every bar, the Composer:

// Updates Strategy Appropriateness

// - Checks the set of ComposerData’s
// - If there are no objects, trigger some CreationStrategy
// - If there are objects, check if there are more than 2 bars worth of data for those instruments to play
// - If not, trigger an UpdateStrategy
void AMusicComposer::OnBeat(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat,
	float BeatFraction)
{

	// Does this ComposerData need more bars defined? 
	int32 BarsDefined = 0;
	for (int i = 0; i < ComposerDataObjects.Num(); i++ )
	{
		FComposerData ComposerData = ComposerDataObjects[i];

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
		if (NumBars - BarsDefined < BarCreationThreshold)
		{
			FInstrumentScheduleData NewSchedule = GenerateBars(ComposerData, BarsDefined, 2);
			ComposerData.ScheduleData.Emplace(NewSchedule);
		}
	}
	
}
