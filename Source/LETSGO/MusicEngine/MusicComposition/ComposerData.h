#pragma once
#include "ComposerData.h"
#include "MusicCompositionStrategy.h"
#include "LETSGO/Instruments/InstrumentNote.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "ComposerData.generated.h"

USTRUCT()
struct FComposerData
{
	GENERATED_BODY()

	FLetsGoGeneratedScale Scale; 

	FInstrumentData InstrumentData;
	int OctaveMin = 1;
	int OctaveMax = 5;

	TArray<FInstrumentScheduleData> ScheduleData;

	// IMusicCompositionStrategy* CompositionStrategy;
	// int ComposerDataObjectIndex;

	FComposerData();
	explicit FComposerData(const FInstrumentData& InData);
};

// Wraps InstrumentSchedule with data specific for Composer. 
USTRUCT()
struct FInstrumentScheduleData
{
	GENERATED_BODY()

	FInstrumentSchedule InstrumentSchedule;
	int StartAtBar;
	int TimesToRepeat;
	IMusicCompositionStrategy* Strategy;

	FInstrumentScheduleData();
	FInstrumentScheduleData(const FInstrumentSchedule& Schedule, int InStartAtBars, int InTimesToRepeat, IMusicCompositionStrategy* Strat);
};


// Wraps a FComposerData with data specific to choosing a new Strategy
USTRUCT()
struct FInstrumentInputData
{
	GENERATED_BODY()

	FComposerData ComposerData;
	float Appropriateness = 0.0f; 
};

USTRUCT()
struct FPossibleStrategy
{
	GENERATED_BODY()

	IMusicCompositionStrategy* Strategy;
	float StrategyAppropriateness = 0.0f;

	TArray<FInstrumentInputData> InstrumentInputs; 
};



/*
UENUM()
enum ESongSection
{
	None,
	Intro,
	Chorus,
	Bridge,
	VerseSection, // Verse has a conflict with some CoreEngine namespace
};

USTRUCT()
struct FSongSections
{
	GENERATED_BODY()

	TEnumAsByte<ESongSection> SongSection;
	int SectionLengthInBars;

	

	FSongSections(): SongSection(None), SectionLengthInBars(0) {}
	FSongSections(const ESongSection InSection, const int InLength): SongSection(InSection), SectionLengthInBars(InLength) {}
};
*/