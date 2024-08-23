// Fill out your copyright notice in the Description page of Project Settings.


#include "InstrumentSchedule.h"

FPerBarSchedule::FPerBarSchedule(UMetaSoundSource* SoundCue, const TArray<float>& Beats)
{
	
	for (int i = 0; i<Beats.Num(); i++)
	{
		NotesInBar.Emplace(FNotesPerBar(Beats[i], SoundCue));
	}
}

FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization, const TArray<FPerBarSchedule>& Pattern)
{
	QuantizationDivision = Quantization;
	BeatSchedule = Pattern;
}

