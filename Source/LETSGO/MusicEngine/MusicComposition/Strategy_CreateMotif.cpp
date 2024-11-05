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
	ScaleDegreeResolution.Add(0, 1.0f); // 1
	ScaleDegreeResolution.Add(1, 0.5f); // 2
	ScaleDegreeResolution.Add(2, 0.5f); // 2
	ScaleDegreeResolution.Add(3, 0.4f); // 3
	ScaleDegreeResolution.Add(4, 0.4f); // 3
	ScaleDegreeResolution.Add(5, 0.6f); // 4
	ScaleDegreeResolution.Add(6, 0.6f); // 4
	ScaleDegreeResolution.Add(7, 0.8f); // 5
	ScaleDegreeResolution.Add(8, 0.8f); // 5
	ScaleDegreeResolution.Add(9, 0.3f); // 6
	ScaleDegreeResolution.Add(10, 0.3f); // 6
	ScaleDegreeResolution.Add(11, 0.9f); // 7

	const TArray SubDivisions {
		EQuartzCommandQuantization::QuarterNote,
		EQuartzCommandQuantization::EighthNote,
		EQuartzCommandQuantization::SixteenthNote,
	};

	float MaxBeatStrength = 0;
	// This is choosing a subdivision at random
	EQuartzCommandQuantization Division = SubDivisions[FMath::RandRange(0, SubDivisions.Num() - 1)];
	int Beats = 0;
	
	switch (Division)
	{
	case EQuartzCommandQuantization::QuarterNote:
		Beats = 4;
		MaxBeatStrength = 0.25f;
	case EQuartzCommandQuantization::EighthNote:
		Beats = 8;
		MaxBeatStrength = 0.5f;
	case EQuartzCommandQuantization::SixteenthNote:
		Beats = 16;
		MaxBeatStrength = 0.75f;
	default:
		Beats = 0;
	}

	// Just like music listeners are conditioned to desire certain notes to resolve
	// We are also carefully attuned to the beat
	// "1 e and a 2 e and a 3 e and a 4 e and a" represents a 16th note bar
	// "1" is stronger than "and" is stronger than "e" or "a"
	// This map attempts to represent that relative strength of beats among various subdivisions
	TMap<int, float> BeatStrength;

	// For zero based arrays, an even number will resolve to the stronger beat of a larger scale degree
	// 16th note [8] resolves to the 8th note [4] resolves to the quarter note [2]
	// 16th note [6] resolves to the 8th note [3] which does not resolve to the quarter note
	// So we recursively modulus check if note is even, increasing strength value each time its divisible
	// This fills our BeatStrengths
	for (int Beat = 0; Beat < Beats; Beat++)
	{
		const float Base = 0.25f;
		float Strength = Base;
		while(Beat % 2 != 0)
		{
			Strength += Base;
			Beat /= 2;
		}
		BeatStrength.Add(Beat, Strength); // [ 0.75, 0.25, 0.5, 0.25, 0.75, 0.25, 0.5, 0.25 ] 16 beat strength array
	}

	State->AllowableNoteIndices;
	TMap<int, float> AllowableNoteMap;

	for (int i = 0; i < State->AllowableNoteIndices.Num(); i++)
	{
		float ScaleDegree = ScaleDegreeResolution.FindRef(State->AllowableNoteIndices[i]); 
		AllowableNoteMap.Add(State->AllowableNoteIndices[i], ScaleDegree);
	}

	float TensionBudget = 0.3;
	float CurrentTension = 0.0f;

	int Octave = FMath::RandRange(CurrentComposerData.OctaveMin, CurrentComposerData.OctaveMax);

	// Add tonic as first note for now 
	FInstrumentNote Note = CurrentComposerData.InstrumentData.GetNote(Octave, State->Scale.Notes[State->AllowableNoteIndices[0]]);
	FPerBarSchedule Schedule;
	FNotesPerBar Test = FNotesPerBar(0, Note.SoundData);
	Schedule.NotesInBar.Add(Test);

	float MaxResolution = MaxBeatStrength + ScaleDegreeResolution.FindRef(0);
	float CumulativeResolution = 0.0f;
	
	for (int i = 0; i < Beats; i++)
	{
		// [0] = 0; [1] = 0.25, etc.
		float Tension = MaxBeatStrength - BeatStrength[i];
		
		// The higher the BeatTension, the more likely we are to rest
		float DefaultRestChance = 0.25; // Convert to non-magic number (put in state)
		float TotalRestChance = DefaultRestChance + Tension;

		int RestChoice = FMath::RandRange(0, 100);
		if (RestChoice >= TotalRestChance * 100)
		{
			continue;
		}
	}
	
	
	// With beat strength and scale degree resolution, we can form a motif
	// We need to return a FPerBarSchedule, which require a set of FNotesPerBar
	// FNotesPerBar need a Beat and SoundData

	// So how do we choose a beat + note?
	// Each has a score: Beat "0" (first beat in bar) and the Tonic would have "strong resolution"
	// Beat[0] = .5f
	// Tonic = 1.0f 
	// [ 1.5f ] // Sum of those two things
	// The higher each sum, the less "tension" there is
	
	// Beat[1] = 0.25
	// 6th = 0.3f
	// [ 1.5f, 0.55f ]
	// Hitting the 6th on the offbeat presents much more tension- we will want it to resolve

	// It could resolve to the Tonic again - [ 1.5f, 0.55f, 1.5f ]
	// However, we could also resolve to - [ 1.5f, 0.55f, 0.95f ]
	// Where the sum of 0.55 and .95 = 1.5
	// Beat[3] is .5, giving us a Note budget of [ 0.55 + .5 ] = 1.05 = 0.45
	// Candidate notes are 3rd (.4f) and 2nd (.5f), maybe even 4th (.6f)
	// So if chosen 2nd [ 1.5f, 0.55f, 1.0f ]

	// Consider also - [ 1.5, 1.5, 1.5, 1.5 ... ] - The "Max" value
	// Consider the sum - [ 1.5, 3.0, 4.5, 6 ... ] Cumulative max 
	// Against ours: [ 1.5f, 0.55f, 1.0f ]
	// Summing our [ 1.5, 2.05, 3.05 ]

	// Gives us a resolution budget?
	// Cumulative sum - constructed motif:
	// [ 0, 0.95, 1.45, ] Gives us total note budget in the bar

	// Let's try a real example - ii - V - i - i
	// Cumulative budget [ 1.25, 2.5, 3.75, 5 ]
	// [ .75, 1.05, 1.25, 1.25 ] ii = .5, V = .8, i = 1
	// [ 0.75, 1.8, 3.05, 4.3 ]
	// [ 0.75, .75
	// This tells us cumulative total doesn't really work, it's always max max
	// But it does give us the maximum resolution
	// We may not reach maximum resolution, but the desire to resolve

	// Let's think about chance to resovle 

	
	// We need something that says "beat 1 has more tension relative to beat 2, resolving in beat 3-4"]
	// Remember, these floats represent their desire to resolve
	// The smaller the number, the stronger the pull to a bigger NEXT number 
	
	// Provides the current instruments Notes.
	// Notes lets us find the SoundData based on Note and Octave
	TArray<FInstrumentNote> Notes = CurrentComposerData.InstrumentData.Notes;

	

	FPerBarSchedule Schedule = FPerBarSchedule();
	
	
	
	
}

float UStrategy_CreateMotif::GetStrategyAppropriateness(const FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
}

float UStrategy_CreateMotif::GetInstrumentAppropriateness(const FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
}
