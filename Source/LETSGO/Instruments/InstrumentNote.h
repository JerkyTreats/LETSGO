// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaSoundPlayerData.h"
#include "MetasoundSource.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "InstrumentNote.generated.h"

/**
 * 
 */
USTRUCT()
struct FInstrumentNote 
{
	GENERATED_BODY()

	UPROPERTY()
	int Octave;

	UPROPERTY()
	TEnumAsByte<ELetsGoMusicNotes> Note;

	UPROPERTY()
	FMetaSoundPlayerData SoundData;


	FInstrumentNote(): Octave(0), Note(C), SoundData(nullptr)
	{
	}

	FInstrumentNote(const int InOctave, const ELetsGoMusicNotes InNote, const FMetaSoundPlayerData& InSoundCue)
	{
		Octave = InOctave;
		Note = InNote;
		SoundData = InSoundCue;
	}
};

USTRUCT()
struct FInstrumentData
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FInstrumentNote> Notes;

	FInstrumentData()
	{
		Notes = TArray<FInstrumentNote>();
	}
	
	explicit FInstrumentData(const TArray<FInstrumentNote>& InNotes)
	{
		Notes = InNotes;
	}

	static FInstrumentData GenerateKeys(TArray<USoundWave*> Sounds);
	FInstrumentNote GetNote(int Octave, FLetsGoMusicNotes Note) const;
};
