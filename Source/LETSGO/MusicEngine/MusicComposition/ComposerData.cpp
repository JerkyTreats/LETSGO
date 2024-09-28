#include "ComposerData.h"


FComposerData::FComposerData()
{
	ScheduleData = TArray<FInstrumentScheduleData>();
}

FComposerData::FComposerData(const FInstrumentData& InData)
{
	FComposerData();
	InstrumentData = InData;
}

FInstrumentScheduleData::FInstrumentScheduleData(): StartAtBar(0), TimesToRepeat(0), Strategy(nullptr)
{
}

FInstrumentScheduleData::FInstrumentScheduleData(const FInstrumentSchedule& Schedule, const int InStartAtBars, const int InTimesToRepeat,
												 IMusicCompositionStrategy* Strat)
{
	InstrumentSchedule = Schedule;
	StartAtBar = InStartAtBars;
	TimesToRepeat = InTimesToRepeat;
	Strategy = Strat;
}