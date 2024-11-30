// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"

#include "Strategy_CreateMotif.h"
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
		NewObject<UStrategy_PedalPointComposition>(),
		NewObject<UStrategy_CreateMotif>()
	};
}

IMusicStrategy* AMusicComposer::ChooseMusicalStrategy(FComposerData& ComposerData, float& AppropriatenessOut)
{
	IMusicStrategy* ChosenStrategy = MusicalStrategies[0];

	TArray<TArray<int>> Candidates;
	
	int Sum = 0;
	
	for(int i = 0; i < MusicalStrategies.Num(); i++)
	{
		IMusicStrategy* CandidateStrategy = MusicalStrategies[i];
		const float CandidateAppropriateness = CandidateStrategy->GetStrategyAppropriateness(
			ComposerData, ComposerState);

		UE_LOG(LogLetsgo, Display, TEXT("Candidate: [%s], Appropriateness: [%f]"), *FString(CandidateStrategy->_getUObject()->GetName()), CandidateAppropriateness)

		int Candidate = CandidateAppropriateness * 100;
		
		Candidates.Emplace(TArray {Sum + 1, Sum + Candidate});
		Sum += Candidate;
		
	}

	const int Pick = FMath::RandRange(1, Sum);
	
	for (int i = 0; i < Candidates.Num(); i++)
	{
		const int Min = Candidates[i][0];
		const int Max = Candidates[i][1];
		
		if (Pick >= Min && Pick <= Max)
		{
			ChosenStrategy = MusicalStrategies[i];
			float Val = Max - (Min - 1);
			Val /= 100;
			AppropriatenessOut = Val;
			break;
		}
	}
	
	UE_LOG(LogLetsgo, Display, TEXT("Chosen Candidate: [%s], Appropriateness: [%f]"), *FString(ChosenStrategy->_getUObject()->GetName()), AppropriatenessOut)

	return ChosenStrategy;
}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (! ComposerState->IsTonicSet)
		return;
	
	int ThisBar = ComposerState->CurrentBar + 2;
	
	if (ThisBar > LastProcessedBar)
	{
		// Does this ComposerData need more bars defined? 
		for (int i = 0; i < ComposerState->ComposerDataObjects->Num(); i++ )
		{
			// Define bars for this instrument
			if ((*ComposerState->ComposerDataObjects)[i].BarsDefined - ThisBar <= ComposerState->BarCreationThreshold)
			{
				UE_LOG(LogLetsgo, Display, TEXT("Composer: Choosing Musical Strategy" ))
				
				float StrategyAppropriateness = 0.0f;
				IMusicStrategy* ChosenStrategy = ChooseMusicalStrategy((*ComposerState->ComposerDataObjects)[i], StrategyAppropriateness);

				if (StrategyAppropriateness < ComposerState->MusicalStrategyAppropriatenessThreshold)
				{
					continue;
				}

				UE_LOG(LogLetsgo, Display, TEXT("Composer: Creating InstrumentSchedule with Strategy [%s]" ), *FString(ChosenStrategy->_getUObject()->GetName()))

				FInstrumentSchedule NewSchedule = ChosenStrategy->GenerateInstrumentSchedule((*ComposerState->ComposerDataObjects)[i], ComposerState, ThisBar);

				(*ComposerState->ComposerDataObjects)[i].EmplaceScheduleData(NewSchedule);
				(*ComposerState->ComposerDataObjects)[i].BarsDefined = ThisBar;
				
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, FString::Printf(TEXT("Number of SchedulesDatas in Composer: [%i]"), (*ComposerState->ComposerDataObjects)[i].ScheduleData->Num()));

			}
		}
		
		LastProcessedBar = ThisBar;
	}
}