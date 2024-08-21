// Fill out your copyright notice in the Description page of Project Settings.


#include "CheeseKeyData.h"

FCheeseKeyData::FCheeseKeyData()
{
}

FCheeseKeyData::FCheeseKeyData(const int SetOctave, const ELetsGoMusicNotes SetNote, UMetaSoundSource* SetSound)
{
	Octave = SetOctave;
	Note = SetNote;
	Sound = SetSound;
}

/**
 * This is some jank. Not pleased at all with this.
 * I'm going to continue on with this until it's end-to-end working though
 * I've decided to go with the most naive possible approach then iterate a better solution
 */ 
TArray<FCheeseKeyData> FCheeseKeyData::GenerateKeys(TArray<UMetaSoundSource*> Sounds)
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
	
	TArray<FCheeseKeyData> KeyData = TArray<FCheeseKeyData>();
	int CurrentOctave = 1;
	
	for (int i = 0; i <= Sounds.Num(); i++)
	{
		if (i % 12 == 0)
		{
			CurrentOctave++;
		}

		const ELetsGoMusicNotes Note = AssumedNoteOrder[i % 12];

		FCheeseKeyData Key = FCheeseKeyData(CurrentOctave, Note, Sounds[i]);
		KeyData.Emplace(Key);
	}

	return KeyData;
}
