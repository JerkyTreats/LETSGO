// Fill out your copyright notice in the Description page of Project Settings.


#include "InstrumentSchedule.h"

FPerBarSchedule::FPerBarSchedule(UMetaSoundSource* SoundCue, TArray<float> Beats)
{
	
	for (int i = 0; i<Beats.Num(); i++)
	{
		FNotesPerBar PerBar = FNotesPerBar(Beats[i], SoundCue);
		NotesInBar.Emplace(PerBar);
	}
}

FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization, const TArray<FPerBarSchedule>& Pattern)
{
	QuantizationDivision = Quantization;
	BeatSchedule = Pattern;
}

