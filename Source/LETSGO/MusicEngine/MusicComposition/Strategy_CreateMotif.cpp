// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_CreateMotif.h"

#include "MusicComposerState.h"

FPerBarSchedule UStrategy_CreateMotif::GenerateBar(const FComposerData& CurrentComposerData,
                                                   const AMusicComposerState* State)
{
	FLetsGoGeneratedScale Scale = State->Scale;

	// Culturally western music listeners are conditioned to desire certain notes to "resolve" to tonic
	// The stronger the pull to resolve, the more tension created if we don't
	// This map tries to represent that desire to resolve 
	TMap<int, float>ScaleDegreeResolution;
	ScaleDegreeResolution.Add(0, 1.0f);
	ScaleDegreeResolution.Add(1, 0.5f);
	ScaleDegreeResolution.Add(2, 0.5f);
	ScaleDegreeResolution.Add(3, 0.4f);
	ScaleDegreeResolution.Add(4, 0.4f);
	ScaleDegreeResolution.Add(5, 0.6f);
	ScaleDegreeResolution.Add(6, 0.6f);
	ScaleDegreeResolution.Add(7, 0.8f);
	ScaleDegreeResolution.Add(8, 0.8f);
	ScaleDegreeResolution.Add(9, 0.3f);
	ScaleDegreeResolution.Add(10, 0.3f);
	ScaleDegreeResolution.Add(11, 0.9f);

	const TArray SubDivisions {
		EQuartzCommandQuantization::QuarterNote,
		EQuartzCommandQuantization::EighthNote,
		EQuartzCommandQuantization::SixteenthNote,
	};

	EQuartzCommandQuantization Division = SubDivisions[FMath::RandRange(0, SubDivisions.Num() - 1)];
	int Beats = 0;
	
	switch (Division)
	{
	case EQuartzCommandQuantization::QuarterNote:
		Beats = 4;
	case EQuartzCommandQuantization::EighthNote:
		Beats = 8;
	case EQuartzCommandQuantization::SixteenthNote:
		Beats = 16;
	default:
		Beats = 0;
	}

	// Just like music listeners are conditioned to desire certain notes to resolve
	// We are also carefully attuned to the beat
	// "1 e and a 2 e and a 3 e and a 4 e and a" represents a 16th note bar
	// "1" is stronger than "and" is stronger than "e" or "a"
	// This map attempts to represent that relative strength of beats among various subdivisions
	TMap<int, float> BeatStrength;

	// For zero based arrays, an even number will resolve to the stronger beat
	// 16th note [8] resolves to the 8th note [4] resolves to the quarter note [2]
	// 16th note [6] resolves to the 8th note [3] which does not resolve to the quarter note
	// So we recursively modulus check if note is even, increasing strength value each time its divisible
	for (int i = 0; i < Beats; i++)
	{
		const float Base = 0.25f;
		float Strength = Base;
		int ThisBeat = i;
		while(ThisBeat % 2 != 0)
		{
			Strength += Base;
			ThisBeat /= 2;
		}
		BeatStrength.Add(i, Strength);
	}

	

	
}

float UStrategy_CreateMotif::GetStrategyAppropriateness(const FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
}

float UStrategy_CreateMotif::GetInstrumentAppropriateness(const FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
}
