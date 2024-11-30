#pragma once

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
	int BarsDefined = 0;

	UPROPERTY()
	int CreateMotifCount = 0;
	
	TSharedPtr<TArray<FInstrumentSchedule>> ScheduleData;

	FComposerData()
	{
		ScheduleData = MakeShared<TArray<FInstrumentSchedule>>();
	}
	
	explicit FComposerData(const EInstrumentRoles InRole, const FInstrumentData& InData);

	bool IsMultiNoteInstrument() const;

	int GetBarsDefined() const;

	void EmplaceScheduleData(FInstrumentSchedule);
};