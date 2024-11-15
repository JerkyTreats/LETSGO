// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_CreateMotif.h"

#include "MusicComposerState.h"

USTRUCT()
struct FPickRange
{
	int Min;
	int Max;
	bool In (int Num)
	{
		return Num >= Min && Num <= Max;
	}

	FPickRange(const int InMin, const int InMax): Min(InMin), Max(InMax) {}
};

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

	int Octave = FMath::RandRange(CurrentComposerData.OctaveMin, CurrentComposerData.OctaveMax);

	// Add tonic as first note for now 
	FInstrumentNote Note = CurrentComposerData.InstrumentData.GetNote(Octave, State->Scale.Notes[State->AllowableNoteIndices[0]]);
	FPerBarSchedule Schedule;
	FNotesPerBar Test = FNotesPerBar(0, Note.SoundData);
	Schedule.NotesInBar.Add(Test);

	float MaxResolution = MaxBeatStrength + ScaleDegreeResolution.FindRef(0);
	float CurrentResolution = MaxResolution;
	float TensionBudget = 0.3f;
	float OptimalTensionPoint = 0.5f;
	int OptimalTensionBonus = 25;
	int WithinTensionBudgetBonus = 50;
	
	for (int i = 1; i < Beats; i++)
	{
		// [0] = 0; [1] = 0.25, etc.
		float Tension = MaxBeatStrength - BeatStrength[i];
		
		// The higher the BeatTension, the more likely we are to rest
		float DefaultRestChance = 0.25; // Convert to non-magic number (put in state)
		float TotalRestChance = DefaultRestChance + Tension;

		if (FMath::RandRange(0, 100) >= TotalRestChance * 100)
		{
			continue;
		}
		
		TArray<FPickRange> Ranges;
		int PickSum = 0;
		for ( int n = 0; n < State->AllowableNoteIndices.Num(); n++)
		{
			// ex. 2nd - 0.5
			float ResolutionWeight = ScaleDegreeResolution.FindRef(State->AllowableNoteIndices[i]);

			float CandidateTotalResolution = CurrentResolution + ResolutionWeight + Tension; // 1.8
			float CurrentMaxResolution = MaxResolution + CurrentResolution; // 2.0
			
			float ResolutionDelta = CurrentMaxResolution - CandidateTotalResolution; // 0.2
			float CandidateTension = ResolutionDelta / CurrentMaxResolution; // 0.1
			
			// Now to determine relationship between 0.1 (CandidateTension) and 0.3 (TensionBudget)
			// If CT < TB, good
			// If current beat count is low, leaving more budget is good
			// If good, multiply chance to pick increased more than less good/bad.
			float BeatPercentage = i / Beats; // Beats[5] = 0.31 - 31%
			float DiffFromOptimalTensionPoint = FMath::Abs(OptimalTensionPoint - BeatPercentage); // .29

			int CandidateWeight = OptimalTensionBonus * DiffFromOptimalTensionPoint; // 7

			if (TensionBudget - CandidateTension > 0)
			{
				CandidateWeight += WithinTensionBudgetBonus;
			}

			// This isn't totally correct. All notes within TensionBudget are flattened to same value.
			// This should probably be corrected in the above if statement
			CandidateWeight *= 100;

			Ranges.Add(FPickRange(PickSum +1, PickSum + CandidateWeight ));
			PickSum += CandidateWeight;
		}

		int Selection = FMath::RandRange(1, PickSum);

		FInstrumentNote SelectedNote;
		
		for (int n = 0; n < Ranges.Num(); n++)
		{
			if (Ranges[0].In(Selection))
			{
				SelectedNote = CurrentComposerData.InstrumentData.GetNote(Octave, State->Scale.Notes[State->AllowableNoteIndices[i]]);
				break;
			}
		}

		Schedule.NotesInBar.Add(FNotesPerBar(i, SelectedNote.SoundData));
	}

	return FPerBarSchedule(Schedule);
}

float UStrategy_CreateMotif::GetStrategyAppropriateness(const FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
}

float UStrategy_CreateMotif::GetInstrumentAppropriateness(const FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
}
