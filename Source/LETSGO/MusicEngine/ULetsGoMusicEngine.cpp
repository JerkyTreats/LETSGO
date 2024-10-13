// Fill out your copyright notice in the Description page of Project Settings.


#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"

void FLetsGoGeneratedScale::GenerateScale(const FLetsGoMusicNotes& InTonic, const FLetsGoMusicScale& Scale)
{
	Notes = TArray
	{
		InTonic,
	};
	
	FLetsGoMusicNotes CurrentNote = InTonic;
		
	for (FLetsGoMusicScaleStep i : Scale.Steps)
	{
		// Get whole = 2 half = 1
		const int Step = i.Step.GetValue();
			
		// Get next step, wrap around to beginning if >12
		int Next = (CurrentNote.Note.GetValue() + Step) % 12;
			
		// Get the Note enum at position "Next"
		FLetsGoMusicNotes NextNote = FLetsGoMusicNotes(static_cast<ELetsGoMusicNotes>(Next));
			
		// Add to Scale
		Notes.Add(NextNote);
			
		// Update CurrentNote for next iteration
		CurrentNote = NextNote;
	}
}

ULetsGoMusicEngine::ULetsGoMusicEngine()
{
}

ULetsGoMusicEngine::~ULetsGoMusicEngine()
{
}

/*
 * Define each Mode
 * https://mixedinkey.com/captain-plugins/wiki/an-introduction-to-modes/
*/

// Ionian		W W H W W W H
const FLetsGoMusicScale ULetsGoMusicEngine::Ionian = FLetsGoMusicScale("Ionian", {
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
});


// Dorian 		W H W W W H W
const FLetsGoMusicScale ULetsGoMusicEngine::Dorian = FLetsGoMusicScale("Dorian", {
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
});

//Phrygian 		H W W W H W W
const FLetsGoMusicScale ULetsGoMusicEngine::Phrygian = FLetsGoMusicScale("Phrygian", {
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
});

// Lydian 		W W W H W W H
const FLetsGoMusicScale ULetsGoMusicEngine::Lydian = FLetsGoMusicScale("Lydian", {
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
});

// Mixolydian 	W W H W W H W
const FLetsGoMusicScale ULetsGoMusicEngine::Mixolydian = FLetsGoMusicScale("Mixolydian", {
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
});

// Aeolian 		W H W W H W W
const FLetsGoMusicScale ULetsGoMusicEngine::Aeolian = FLetsGoMusicScale("Aeolian", {
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
});

// Locrian 		H W W H W W W
const FLetsGoMusicScale ULetsGoMusicEngine::Locrian = FLetsGoMusicScale("Locrian", {
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
	{ ELetsGoMusicScaleSteps::Whole },
});

const FLetsGoMusicScale ULetsGoMusicEngine::Chromatic = FLetsGoMusicScale("Chromatic", {
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
	{ ELetsGoMusicScaleSteps::Half },
});

const FLetsGoMusicScale ULetsGoMusicEngine::WholeStep = FLetsGoMusicScale("WholeStep", {
	{Whole},
	{Whole},
	{Whole},
	{Whole},
	{Whole},
});

/*const FLetsGoMusicScale ULetsGoMusicEngine::MajorPentatonic = FLetsGoMusicScale("Major Pentatonic", {
	{Whole},
	{Whole},
	{Whole},
	{Whole}
});*/


FLetsGoMusicScale ULetsGoMusicEngine::GetScale(const ELetsGoMusicScales Scale)
{
	switch (Scale)
	{
	case ELetsGoMusicScales::Ionian:
		return Ionian;

	case ELetsGoMusicScales::Dorian:
		return Dorian;

	case ELetsGoMusicScales::Phrygian:
		return Phrygian;

	case ELetsGoMusicScales::Lydian:
		return Lydian;

	case ELetsGoMusicScales::Mixolydian:
		return Mixolydian;

	case ELetsGoMusicScales::Aeolian:
		return Aeolian;

	case ELetsGoMusicScales::Locrian:
		return Locrian;

	case ELetsGoMusicScales::Chromatic:
		return Chromatic;

	case ELetsGoMusicScales::WholeStep:
		return Chromatic;
			
	default:
		return Ionian;
	}
}

FLetsGoMusicNotes ULetsGoMusicEngine::GetNote(const ELetsGoMusicNotes Note)
{
	return FLetsGoMusicNotes(Note);
}

FLetsGoGeneratedScale ULetsGoMusicEngine::GenerateScale(const FLetsGoMusicScale& Scale, const FLetsGoMusicNotes& Tonic)
{
	FLetsGoGeneratedScale GeneratedScale = FLetsGoGeneratedScale(Tonic, Scale);
	
	return GeneratedScale;
}

TArray<FLetsGoGeneratedScale> ULetsGoMusicEngine::GenerateAllScales(const FLetsGoMusicNotes& Tonic)
{
	TArray<FLetsGoGeneratedScale> AllGeneratedScales;

	// I originally had this defined in header as an inline static constant, which worked.
	// Annnnd then it suddenly didn't.
	// Defining it in here does work, which is so far the only place I need it.
	// So that's cool. Great comment. No feedback required. 
	TArray AllScales = {
		Ionian,
		Dorian,
		Phrygian,
		Lydian,
		Mixolydian,
		Aeolian,
		Locrian,
		// Pentatonic,
		Chromatic,
		WholeStep,
	};

	for (int i = 0; i < AllScales.Num(); i++ )
	{
		FLetsGoGeneratedScale GeneratedScale = GenerateScale(AllScales[i], Tonic);
		AllGeneratedScales.Add(GeneratedScale);
	}
	
	return AllGeneratedScales;
}

//          2nd      3rd      4th     5th      6th   7th
// "{ C, [Db, D], [Eb, E], [Fb, F], [G, G#], [A, A#], B }"
//    1  ♯1   2    ♯2  3    4♯  4    5  ♯5    6 ♯6    7  (Chromatic Scale Intervals)
TArray<int> ULetsGoMusicEngine::GetInterval(const int DesiredInterval)
{
	// Get one less than the Desired interval 
	// ex. 5th IntervalBase = Scale[6] (D# if Tonic = C)
	const int IntervalBase = (DesiredInterval - 2) * 2;

	TArray Interval = {
		IntervalBase + 1, // Scale[7] = "G" for Tonic = C
		IntervalBase + 2  // Scale[8] = "G#"
	};

	return Interval;
}
