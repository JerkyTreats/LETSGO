// Fill out your copyright notice in the Description page of Project Settings.


#include "InstrumentSchedule.h"

FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization, const TArray<FPerBarSchedule>& Pattern)
{
	QuantizationDivision = Quantization;
	BeatSchedule = Pattern;
}


/*FInstrumentSchedule::FInstrumentSchedule(const EQuartzCommandQuantization Quantization, const TArray<float>& Pattern)
{
	QuantizationDivision = Quantization;

	const FPerBarSchedule PerBar = FPerBarSchedule(Pattern);
	const TArray PerBarArr = { PerBar };
	BeatSchedule = PerBarArr;
}*/
