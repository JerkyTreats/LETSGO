﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_CreateMotif.h"

#include "MusicComposerState.h"

USTRUCT()
struct FCreateMotifData
{
	UPROPERTY()
	float TensionBudget = 0.3f;

	UPROPERTY()
	float OptimalTensionPoint = 0.5f;

	UPROPERTY()
	int OptimalTensionBonus = 25;

	UPROPERTY()
	int WithinTensionBudgetBonus = 50;

	UPROPERTY()
	float BaseBeatStrength = 0.25f;
	
	UPROPERTY()
	TMap<int, float>ScaleDegreeResolution;

	UPROPERTY()
	EQuartzCommandQuantization Division;

	UPROPERTY()
	int Beats;

	UPROPERTY()
	float MaxBeatStrength;

	UPROPERTY()
	TMap<int, float> BeatStrength;

	FCreateMotifData()
	{
		// Culturally western music listeners are conditioned to desire certain notes to "resolve" to tonic
		// The stronger the pull to resolve, the more tension created if we don't
		// This map tries to represent that desire to resolve 
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

		// Ordered
		const TArray SubDivisions {
        	EQuartzCommandQuantization::QuarterNote,
			EQuartzCommandQuantization::EighthNote,
			EQuartzCommandQuantization::SixteenthNote,
        };


		const int DivPick = FMath::RandRange(0, SubDivisions.Num() - 1);
        // This is choosing a subdivision at random
        Division = SubDivisions[DivPick];

		switch (Division)
        {
        case EQuartzCommandQuantization::QuarterNote:
        	Beats = 4;
        	break;
        case EQuartzCommandQuantization::EighthNote:
	        Beats = 8;
        	break;
        case EQuartzCommandQuantization::SixteenthNote:
	        Beats = 16;
        	break;
        default:
	        Beats = 0;
        }

		MaxBeatStrength = BaseBeatStrength * (DivPick + 1); 
		BeatStrength = TMap<int, float>();

		// This probably doesn't scale to 32, but I think this works
		for (int b = 0; b < Beats; b++)
		{
			float Strength;
			const float SmallestStrength = MaxBeatStrength / SubDivisions.Num();

			// This (Beats / 4) is somewhat magical, but works.
			// At least if the time signature is 4/4
			switch (b % (Beats / 4)) 
			{
			case(0):
				Strength = MaxBeatStrength;
				break;
			case(2):
				Strength = MaxBeatStrength - SmallestStrength;
				break;
			case(1):
				Strength = MaxBeatStrength - (SmallestStrength * 2);
				break;
			case(3):
				Strength = MaxBeatStrength - (SmallestStrength * 2);
				break;
			default:
				Strength = 0.0f;
			}
			
			BeatStrength.Add(b, Strength);
			// [ 0.75, 0.25, 0.5, 0.25, 0.75, 0.25, 0.5, 0.25... ] 16 beat strength array
			// [ 0.50, 0.25, 0.5, 0.25...] 8 beat strength array
			// [ 0.25, 0.25, 0.25, 0.25 ] 4 beat 
		}
	}
};

USTRUCT()
struct FNoteCandidate
{
	int Min;
	int Max;
	
	float Resolution;
	float Tension;

	FInstrumentNote Note;
	
	bool In (int Num)
	{
		return Num >= Min && Num <= Max;
	}

	FNoteCandidate(const int InMin, const int InMax, const float InResolution, const float InTension, FInstrumentNote InNote): Min(InMin), Max(InMax), Resolution(InResolution), Tension(InTension), Note(InNote) {}
};

FInstrumentSchedule UStrategy_CreateMotif::GenerateInstrumentSchedule(FComposerData& CurrentComposerData,
                                                                      const AMusicComposerState* State, const int StartAtBar)
{
	FCreateMotifData Data = FCreateMotifData();
	
	FLetsGoGeneratedScale Scale = State->Scale;

	int Octave = FMath::RandRange(CurrentComposerData.OctaveMin, CurrentComposerData.OctaveMax);

	// Add tonic as first note for now 
	FInstrumentNote Note = CurrentComposerData.InstrumentData.GetNote(Octave, State->Scale.Notes[State->AllowableNoteIndices[0]]);
	FPerBarSchedule Schedule;
	FNotesPerBar Test = FNotesPerBar(0, Note.SoundData);
	Schedule.NotesInBar.Add(Test);

	float MaxResolution = Data.MaxBeatStrength + Data.ScaleDegreeResolution.FindRef(0);
	float CurrentResolution = MaxResolution;

	float CurrentTensionBudget = Data.TensionBudget;
	
	for (int i = 0; i < Data.Beats; i++)
	{
		// [0] = 0; [1] = 0.25, etc.
		float Tension = Data.MaxBeatStrength - Data.BeatStrength[i];
		
		// The higher the BeatTension, the more likely we are to rest
		float DefaultRestChance = 0.25; // Convert to non-magic number (put in state)
		float TotalRestChance = DefaultRestChance + Tension;

		if (FMath::RandRange(0, 100) >= TotalRestChance * 100)
		{
			continue;
		}
		
		TArray<FNoteCandidate> Ranges;
		int PickSum = 0;
		for ( int n = 0; n < State->AllowableNoteIndices.Num(); n++)
		{
			// ex. 2nd - 0.5
			float ResolutionWeight = Data.ScaleDegreeResolution.FindRef(State->AllowableNoteIndices[n]);

			float CandidateTotalResolution = CurrentResolution + ResolutionWeight + Tension; // 1.8
			float CurrentMaxResolution = MaxResolution + CurrentResolution; // 2.0
			
			float ResolutionDelta = CurrentMaxResolution - CandidateTotalResolution; // 0.2
			float CandidateTension = ResolutionDelta / CurrentMaxResolution; // 0.1
			
			// Now to determine relationship between 0.1 (CandidateTension) and 0.3 (TensionBudget)
			// If CT < TB, good
			// If current beat count is low, leaving more budget is good
			// If good, multiply chance to pick increased more than less good/bad.
			float BeatPercentage = i / Data.Beats; // Beats[5] = 0.31 - 31%
			float DiffFromOptimalTensionPoint = FMath::Abs(Data.OptimalTensionPoint - BeatPercentage); // .29

			int CandidateWeight = (CandidateTension * 100) + (Data.OptimalTensionBonus * DiffFromOptimalTensionPoint); // 10 + 7

			if (CurrentTensionBudget - CandidateTension > 0)
			{
				CandidateWeight += Data.WithinTensionBudgetBonus;
			}

			Ranges.Add(FNoteCandidate(PickSum +1, PickSum + CandidateWeight, ResolutionWeight + Data.BeatStrength[i], CandidateTension, CurrentComposerData.InstrumentData.GetNote(Octave, State->Scale.Notes[State->AllowableNoteIndices[n]])));
			PickSum += CandidateWeight;
		}

		int Selection = FMath::RandRange(1, PickSum);

		FInstrumentNote SelectedNote;
		
		for (int n = 0; n < Ranges.Num(); n++)
		{
			if (Ranges[n].In(Selection))
			{
				SelectedNote = Ranges[n].Note;
				CurrentResolution += Ranges[n].Resolution;
				CurrentTensionBudget -= Ranges[n].Tension;
				break;
			}
		}

		Schedule.NotesInBar.Add(FNotesPerBar(i, SelectedNote.SoundData));
	}

	CurrentComposerData.CreateMotifCount++;
	
	TArray<FPerBarSchedule> PerBarSchedules = TArray { FPerBarSchedule(Schedule) };
	FInstrumentSchedule InstrumentSchedule = FInstrumentSchedule(Data.Division, PerBarSchedules, StartAtBar);
	return InstrumentSchedule;
}

float UStrategy_CreateMotif::GetStrategyAppropriateness(FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
	if (! CurrentComposerData.IsMultiNoteInstrument() || State->AllowableNoteIndices.Num() == 0)
	{
		return 0.0f;
	}

	float Weight = 0.8f;

	if (CurrentComposerData.InstrumentRole == Bass)
	{
		Weight -= 0.1f;
	}

	for (int i = 0; i < State->ComposerDataObjects->Num(); i++)
	{
		if ((*State->ComposerDataObjects)[i].CreateMotifCount > 0) {
			Weight -= 0.3f;
			break;
		}
		
	}

	return Weight;
}

float UStrategy_CreateMotif::GetInstrumentAppropriateness(FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
	return 0.0f;
}
