// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FLetsGoMusicNotes Note;

	UPROPERTY()
	UMetaSoundSource* SoundCue;

	FInstrumentNote(): Octave(0), SoundCue(nullptr){}

	FInstrumentNote(int octave, ELetsGoMusicNotes note, UMetaSoundSource* soundCue)
	{
		Octave = octave;
		Note = FLetsGoMusicNotes(note);
		SoundCue = soundCue;
	}
};
