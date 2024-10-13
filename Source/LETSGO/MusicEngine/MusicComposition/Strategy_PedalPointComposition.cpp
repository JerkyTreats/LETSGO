// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_PedalPointComposition.h"

#include "ComposerData.h"
#include "MusicComposerState.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"

FInstrumentSchedule UStrategy_PedalPointComposition::Apply(TSharedPtr<FComposerData> CurrentComposerData, FInstrumentScheduleData InstrumentScheduleData)
{
	// Filter the array
	TArray<FInstrumentNote> FilteredNotes = CurrentComposerData->InstrumentData.Notes.FilterByPredicate([&] (const FInstrumentNote& InstrumentNote){
		return InstrumentNote.Octave == CurrentComposerData->OctaveMin && InstrumentNote.Note == CurrentComposerData->Scale.Tonic.Note;
	});
	
	FInstrumentSchedule Schedule = FInstrumentSchedule();

	Schedule.QuantizationDivision = EQuartzCommandQuantization::QuarterNote;
	FPerBarSchedule Bar =  FPerBarSchedule({
		FNotesPerBar(1.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(2.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(3.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(4.0f, FilteredNotes[0].SoundData),
	});
	
	for (int i = 0; i < InstrumentScheduleData.TimesToRepeat; i++ )
	{
		Schedule.BeatSchedule.Emplace(Bar);
	}
	
	return Schedule;
}

float UStrategy_PedalPointComposition::GetStrategyAppropriateness(TSharedPtr<FComposerData> CurrentComposerData, const AMusicComposerState* State)
{
	if (! CurrentComposerData->IsMultiNoteInstrument() || State->AllowableNoteIndices.Num() == 0)
	{
		return 0.0f;
	}

	float Weight = 1.0f;

	for (int i = 0; i < State->ComposerDataObjects.Num(); i++)
	{
		FComposerData ComposerData = State->ComposerDataObjects[i];
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
float UStrategy_PedalPointComposition::GetInstrumentAppropriateness(TSharedPtr<FComposerData> CurrentComposerData,
	const AMusicComposerState* State)
{
	return 0.0f;
}

