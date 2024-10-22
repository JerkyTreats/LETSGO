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
	InitializeComposerData();
	InitializeStrategies();
	
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
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, FString::Printf(TEXT("Bass: [%i]"), Bass.ScheduleData->Num()));

	
	FComposerData Tenor = FComposerData(EInstrumentRoles::Tenor, CheeseInstrumentData);
	Tenor.OctaveMin = 3;
	Tenor.OctaveMax = 3;
	
	FComposerData Alto = FComposerData(EInstrumentRoles::Alto, CheeseInstrumentData);
	Alto.OctaveMin = 4;
	Alto.OctaveMax = 4;
	
	FComposerData Soprano = FComposerData(EInstrumentRoles::Soprano, CheeseInstrumentData);
	Soprano.OctaveMin = 5;
	Soprano.OctaveMax = 5;
	
	
	TArray Roles {
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

	for (FComposerData Data : Roles)
	{
		ComposerState->ComposerDataObjects->Emplace(Data);
	}
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

//FInstrumentSchedule AMusicComposer::GenerateBars(FComposerData Data)
///{

	//
	// Data->EmplaceScheduleData(NewSchedule);
	// Data->BarsDefined = LastProcessedBar + TimesToRepeat;
	//
	// if(GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Emplaced New Schedule at bar [%i]"), NewSchedule.StartAtBar));/
//}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (! ComposerState->IsTonicSet)
		return;
	
	int ThisBar = ComposerState->CurrentBar + 4;

	/*if (! Started)
	{
		ThisBar += 2;
		Started = true;
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Started")));
	}*/
	
	if (ThisBar > LastProcessedBar)
	{
		// Does this ComposerData need more bars defined? 
		for (int i = 0; i < ComposerState->ComposerDataObjects->Num(); i++ )
		{
			// TSharedPtr<FComposerData> ComposerData = MakeShared<FComposerData>((*ComposerState->ComposerDataObjects)[i]);

			// Define bars for this instrument
			if ((*ComposerState->ComposerDataObjects)[i].BarsDefined - LastProcessedBar <= ComposerState->BarCreationThreshold)
			{

				float StrategyAppropriateness = 0.0f;
				IMusicStrategy* ChosenStrategy = ChooseMusicalStrategy((*ComposerState->ComposerDataObjects)[i], StrategyAppropriateness);

				if (StrategyAppropriateness < ComposerState->MusicalStrategyAppropriatenessThreshold)
					return;

				FComposerData Data = (*ComposerState->ComposerDataObjects)[i];
				FPerBarSchedule Bar = ChosenStrategy->GenerateBar(Data, ComposerState);
	
				//TODO Times to Repeat magic number
				const int TimesToRepeat = 2;

				FInstrumentSchedule NewSchedule = FInstrumentSchedule(EQuartzCommandQuantization::QuarterNote, Bar, TimesToRepeat, LastProcessedBar + 1);
				
				(*ComposerState->ComposerDataObjects)[i].EmplaceScheduleData(NewSchedule);
				(*ComposerState->ComposerDataObjects)[i].BarsDefined = LastProcessedBar + TimesToRepeat;
				
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, FString::Printf(TEXT("Number of SchedulesDatas in Composer: [%i]"), (*ComposerState->ComposerDataObjects)[i].ScheduleData->Num()));

			}
		}
		
		LastProcessedBar = ThisBar;
	}
}