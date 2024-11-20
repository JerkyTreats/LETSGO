// Fill out your copyright notice in the Description page of Project Settings.


#include "InstrumentSchedule.h"

FPerBarSchedule::FPerBarSchedule(USoundWave* SoundCue, TArray<float> Beats)
{
	
	for (int i = 0; i<Beats.Num(); i++)
	{
		FNotesPerBar PerBar = FNotesPerBar(Beats[i], SoundCue);
		NotesInBar.Emplace(PerBar);
	}
}

FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization,
	const TArray<FPerBarSchedule>& Pattern)
{
	QuantizationDivision = Quantization;
	BeatSchedule = Pattern;
	StartAtBar = 0;
}

FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization, const TArray<FPerBarSchedule>& Pattern, const int BarStart)
{
	QuantizationDivision = Quantization;
	BeatSchedule = Pattern;
	StartAtBar = BarStart;
}

FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization,
	const FPerBarSchedule& Pattern, const int TimesToRepeat, const int BarStart)
{
	QuantizationDivision = Quantization;
	StartAtBar = BarStart;
	for (int i = 0; i < TimesToRepeat; i++)
	{
		BeatSchedule.Emplace(Pattern);
	}
}

