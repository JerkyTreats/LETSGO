#pragma once

#include "MusicStrategy.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/Instruments/Instrument.h"
#include "LETSGO/Instruments/InstrumentNote.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "ComposerData.generated.h"

UENUM()
enum EInstrumentRoles
{
	None,

	// 4 Part Harmony
	Bass,
	Tenor,
	Alto,
	Soprano,

	// Drums
	Kick,
	Snare,
	HiHatClosed,
	HiHatOpen,
	Clap,
};

UENUM()
enum EMusicStrategies
{
	PedalPoint,
	CreateMotif,
};

USTRUCT()
struct FMusicStrategyData
{
	GENERATED_BODY()

	IMusicStrategy* Strategy;

	UPROPERTY()
	TEnumAsByte<EMusicStrategies> StrategyType;

	UPROPERTY()
	float StrategyAppropriateness = 0.0f;

	// TArray<FInstrumentInputData> InstrumentInputs;


	FMusicStrategyData();
	FMusicStrategyData(IMusicStrategy* InputStrategy, float Appropriateness, const EMusicStrategies InStrategyType);

	// void GenerateInstrumentInputs(const TArray<FComposerData> ComposerDataSet);
};

// Wraps InstrumentSchedule with data specific for Composer. 
USTRUCT()
struct FInstrumentScheduleData
{
	GENERATED_BODY()

	UPROPERTY()
	FInstrumentSchedule InstrumentSchedule;

	UPROPERTY()
	int StartAtBar = 0;

	UPROPERTY()
	int TimesToRepeat = 0;

	UPROPERTY()
	FMusicStrategyData StrategyData;

	UPROPERTY()
	bool IsValid = false;

	FInstrumentScheduleData()
	{
		UE_LOG(LogLetsgo, Warning, TEXT("Default FInstrumentScheduleData Constructor used."));
	}

	FInstrumentScheduleData(const FInstrumentSchedule& Schedule, int InStartAtBars, int InTimesToRepeat);
};


// Represents another Instrument that may be influential to a Musical Strategy
// eg. A `Call and Response` strat needs instruments to listen to each other.
// This object facilitates the data needed for such a strategy.
/*USTRUCT()
struct FInstrumentInputData
{
	GENERATED_BODY()

	FComposerData ComposerData;
	float Appropriateness = 0.0f;

	FInstrumentInputData() {}
	explicit FInstrumentInputData(const FComposerData& InputData);
};*/



USTRUCT()
struct FComposerData
{
	GENERATED_BODY()

	UPROPERTY()
	FLetsGoGeneratedScale Scale; 

	UPROPERTY()
	TEnumAsByte<EInstrumentRoles> InstrumentRole = None;

	UPROPERTY()
	FInstrumentData InstrumentData;
	
	UPROPERTY()
	int OctaveMin = 1;

	UPROPERTY()
	int OctaveMax = 5;

	UPROPERTY()
	TArray<FInstrumentScheduleData> ScheduleData;

	// IMusicCompositionStrategy* CompositionStrategy;
	// int ComposerDataObjectIndex;

	FComposerData()
	{
		ScheduleData = TArray<FInstrumentScheduleData>();
	}

	explicit FComposerData(const EInstrumentRoles InRole, const FInstrumentData& InData);

	bool IsMultiNoteInstrument() const;
};