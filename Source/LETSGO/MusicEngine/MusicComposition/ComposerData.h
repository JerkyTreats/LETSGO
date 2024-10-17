#pragma once

#include "LETSGO/Instruments/Instrument.h"
#include "LETSGO/Instruments/InstrumentNote.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
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

/*UENUM()
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


	FMusicStrategyData();
	FMusicStrategyData(IMusicStrategy* InputStrategy, float Appropriateness, const EMusicStrategies InStrategyType);
};*/

/*// Wraps InstrumentSchedule with data specific for Composer. 
USTRUCT()
struct FInstrumentScheduleData
{
	GENERATED_BODY()

	UPROPERTY()
	FInstrumentSchedule InstrumentSchedule;
	
	UPROPERTY()
	FMusicStrategyData StrategyData;

	FInstrumentScheduleData()
	{
		UE_LOG(LogLetsgo, Warning, TEXT("Default FInstrumentScheduleData Constructor used."));
	}

	FInstrumentScheduleData(const FInstrumentSchedule& Schedule, int InStartAtBars, int InTimesToRepeat)
	{
		InstrumentSchedule = Schedule;
	}
};*/


USTRUCT()
struct FComposerData
{
	GENERATED_BODY()

	UPROPERTY()
	TEnumAsByte<EInstrumentRoles> InstrumentRole = None;

	UPROPERTY()
	FInstrumentData InstrumentData;
	
	UPROPERTY()
	int OctaveMin = 1;

	UPROPERTY()
	int OctaveMax = 5;

	UPROPERTY()
	AInstrument* Instrument; 
	
	TArray<FInstrumentSchedule> ScheduleData;

	FComposerData()
	{
		ScheduleData = TArray<FInstrumentSchedule>();
	}

	explicit FComposerData(const EInstrumentRoles InRole, const FInstrumentData& InData);

	bool IsMultiNoteInstrument() const;
};