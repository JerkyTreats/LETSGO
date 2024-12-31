#include "ComposerData.h"


FComposerData::FComposerData(const EInstrumentRoles InRole, const FInstrumentData& InData)
{
	InstrumentRole = InRole;
	InstrumentData = InData;
	ScheduleData = MakeShared<TArray<FInstrumentSchedule>>();
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

int FComposerData::GetBarsDefined() const
{
	return BarsDefined;
}

void FComposerData::EmplaceScheduleData(FInstrumentSchedule Schedule)
{
	ScheduleData->Emplace(Schedule);
	BarsDefined = Schedule.StartAtBar + Schedule.BeatSchedule.Num();
}
