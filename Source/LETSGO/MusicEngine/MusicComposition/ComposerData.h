#pragma once

#include "MusicStrategyData.h"
#include "LETSGO/LETSGO.h"
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

// Wraps InstrumentSchedule with data specific for Composer. 
USTRUCT()
struct FInstrumentScheduleData
{
	GENERATED_BODY()

	FInstrumentSchedule InstrumentSchedule;
	int StartAtBar = 0;
	int TimesToRepeat = 0;
	FMusicStrategyData StrategyData;
	

	FInstrumentScheduleData()
	{
		UE_LOG(LogLetsgo, Warning, TEXT("Default FInstrumentScheduleData Constructor used."));
	}

	FInstrumentScheduleData(const FInstrumentSchedule& Schedule, int InStartAtBars, int InTimesToRepeat);

	
};


USTRUCT()
struct FComposerData
{
	GENERATED_BODY()

	FLetsGoGeneratedScale Scale; 

	TEnumAsByte<EInstrumentRoles> InstrumentRole = None;
	FInstrumentData InstrumentData;
	int OctaveMin = 1;
	int OctaveMax = 5;

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

// Represents another Instrument that may be influential to a Musical Strategy
// eg. A `Call and Response` strat needs instruments to listen to each other.
// This object facilitates the data needed for such a strategy.
USTRUCT()
struct FInstrumentInputData
{
	GENERATED_BODY()

	FComposerData ComposerData;
	float Appropriateness = 0.0f;

	FInstrumentInputData() {}
	explicit FInstrumentInputData(const FComposerData& InputData);
};

