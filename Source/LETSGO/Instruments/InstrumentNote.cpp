// Fill out your copyright notice in the Description page of Project Settings.


#include "InstrumentNote.h"


/**
 * This is some jank. Not pleased at all with this.
 * I'm going to continue on with this until it's end-to-end working though
 * I've decided to go with the most naive possible approach then iterate a better solution
 */ 
FInstrumentData FInstrumentData::GenerateKeys(TArray<USoundWave*> Sounds)
{
	TArray<ELetsGoMusicNotes> AssumedNoteOrder = {
		C,
		CSharp,
		D,
		EFlat,
		E,
		F,
		FSharp,
		G,
		AFlat,
		A,
		BFlat,
		B,
	};
	
	TArray<FInstrumentNote> KeyData = TArray<FInstrumentNote>();
	int CurrentOctave = 1;
	
	for (int i = 0; i < Sounds.Num(); i++)
	{
		if (i % 12 == 0)
		{
			CurrentOctave++;
		}

		const ELetsGoMusicNotes Note = AssumedNoteOrder[i % 12];

		FMetaSoundPlayerData SoundData = FMetaSoundPlayerData(Sounds[i]);
		FInstrumentNote Key = FInstrumentNote(CurrentOctave, Note, SoundData);
		KeyData.Emplace(Key);
	}

	return FInstrumentData(KeyData);
}

FInstrumentNote FInstrumentData::GetNote(const int Octave, const FLetsGoMusicNotes Note) const
{
	// Filter the array
	TArray<FInstrumentNote> FilteredNotes = Notes.FilterByPredicate([&] (const FInstrumentNote& InstrumentNote){
		return InstrumentNote.Octave == Octave && InstrumentNote.Note == Note.Note;
	});

	if (FilteredNotes.Num() > 1)
	{
		UE_LOG(LogLetsgo, Error, TEXT("FInstrumentData::GetNote returned >1 sized filter array, returning first value"));
		return FilteredNotes[0];
	}

	if (FilteredNotes.Num() == 0)
	{
		UE_LOG(LogLetsgo, Error, TEXT("FInstrumentData::GetNote return 0 sized filter array, returning nullish value"));
		return FInstrumentNote();
	}

	return FilteredNotes[0];
}
