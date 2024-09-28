// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_PedalPointComposition.h"

#include "ComposerData.h"
#include "MusicComposer.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "LETSGO/Instruments/Cheese Keys/CheeseKeySoundCueMapping.h"

FInstrumentSchedule UStrategy_PedalPointComposition::Apply(FComposerData& Data)
{
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode()); 
	ACheeseKeySoundCueMapping* CheeseKeyMapping = GameMode->GetInstrumentData_CheeseKey();

	// TODO Fix Octave shenan
	// TODO AudioCuePlayer has exact same logic. Bad? 
	// Filter the array
	TArray<FInstrumentNote> FilteredNotes = CheeseKeyMapping->NoteData.Notes.FilterByPredicate([&] (const FInstrumentNote& CheeseData){
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

