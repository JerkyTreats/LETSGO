// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_PedalPointComposition.h"

#include "ComposerData.h"
#include "MusicComposerState.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"

FInstrumentSchedule UStrategy_PedalPointComposition::GenerateInstrumentSchedule(FComposerData& CurrentComposerData, const AMusicComposerState* State, const int StartAtBar)
{
	// Filter the array
	TArray<FInstrumentNote> FilteredNotes = CurrentComposerData.InstrumentData.Notes.FilterByPredicate([&] (const FInstrumentNote& InstrumentNote){
		return InstrumentNote.Octave == CurrentComposerData.OctaveMin && InstrumentNote.Note == State->Scale.Tonic.Note;
	});
	
	FPerBarSchedule Bar =  FPerBarSchedule({
		FNotesPerBar(1.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(2.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(3.0f, FilteredNotes[0].SoundData),
		FNotesPerBar(4.0f, FilteredNotes[0].SoundData),
	});

	TArray<FPerBarSchedule> Bars = TArray { Bar };
	FInstrumentSchedule InstrumentSchedule = FInstrumentSchedule(EQuartzCommandQuantization::QuarterNote, Bars, StartAtBar);
	return InstrumentSchedule;
}

float UStrategy_PedalPointComposition::GetStrategyAppropriateness(FComposerData& CurrentComposerData, const AMusicComposerState* State)
{
	if (! CurrentComposerData.IsMultiNoteInstrument() || State->AllowableNoteIndices.Num() == 0)
	{
		return 0.0f;
	}

	float Weight = 0.2f;

	if (CurrentComposerData.InstrumentRole == Bass)
	{
		Weight += 0.3f;
	}

	if (CurrentComposerData.ScheduleData->Num() == 0)
	{
		Weight += 0.3;
	}
	
	return Weight;
}

// This strategy doesn't need input from other instruments
float UStrategy_PedalPointComposition::GetInstrumentAppropriateness(FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
	return 0.0f;
}

