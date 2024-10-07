#include "ComposerData.h"


FComposerData::FComposerData(const EInstrumentRoles InRole, const FInstrumentData& InData)
{
	FComposerData();
	InstrumentRole = InRole;
	InstrumentData = InData;
}

bool FComposerData::IsMultiNoteInstrument() const
{
	switch (InstrumentRole)
	{
	case Kick:
		return false;
	case HiHatClosed:
		return false;
	case HiHatOpen:
		return false;
	case Snare:
		return false;
	case Clap:
		return false;
	default:
		return true;
	}
}

FInstrumentScheduleData::FInstrumentScheduleData(const FInstrumentSchedule& Schedule, const int InStartAtBars, const int InTimesToRepeat)
{
	InstrumentSchedule = Schedule;
	StartAtBar = InStartAtBars;
	TimesToRepeat = InTimesToRepeat;
}

FInstrumentInputData::FInstrumentInputData(const FComposerData& InputData)
{
	ComposerData = InputData;
}


