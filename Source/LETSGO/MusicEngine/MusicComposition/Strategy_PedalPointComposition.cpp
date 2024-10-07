// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_PedalPointComposition.h"

#include "ComposerData.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/Instruments/Cheese Keys/CheeseKeySoundCueMapping.h"

FInstrumentSchedule UStrategy_PedalPointComposition::Apply(FComposerData& Data)
{
	// Filter the array
	TArray<FInstrumentNote> FilteredNotes = Data.InstrumentData.Notes.FilterByPredicate([&] (const FInstrumentNote& CheeseData){
		return CheeseData.Octave == Data.OctaveMin && CheeseData.Note == Data.Scale.Tonic.Note;
	});
	
	FInstrumentSchedule Schedule = FInstrumentSchedule();

	Schedule.QuantizationDivision = EQuartzCommandQuantization::QuarterNote;
	TArray<FNotesPerBar> Beats {
		FNotesPerBar(1.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(2.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(3.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(4.0f, FilteredNotes[0].SoundData),
	};
	
	return Schedule;
}

float UStrategy_PedalPointComposition::GetStrategyAppropriateness(FComposerData CurrentComposerData, TArray<FComposerData> ComposerDataSet, FLetsGoGeneratedScale Scale)
{
	if (Scale.IsValid ||
		! Scale.Tonic.Note ||
		! CurrentComposerData.IsMultiNoteInstrument())
	{
		return 0.0f;
	}

	float Weight = 1.0f;

	for (int i = 0; i < ComposerDataSet.Num(); i++)
	{
		FComposerData ComposerData = ComposerDataSet[i];
		for (int ScheduleDataIndex = 0; ScheduleDataIndex < ComposerData.ScheduleData.Num(); ScheduleDataIndex++)
		{
			if (FInstrumentScheduleData ScheduleData = ComposerData.ScheduleData[i]; ScheduleData.StrategyData.StrategyType == CreateMotif)
			{
				Weight = 0.5f;
			}
		}
	}
	
	return Weight;
}

// This strategy doesn't need input from other instruments
float UStrategy_PedalPointComposition::GetInstrumentAppropriateness(FComposerData CurrentComposerData,
	TArray<FComposerData> ComposerDataSet)
{
	return 0.0f;
}

