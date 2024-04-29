// Fill out your copyright notice in the Description page of Project Settings.


#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"

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
	
	GeneratedScale.Notes = TArray<FLetsGoMusicNotes>();
	GeneratedScale.Notes.Add(Tonic);
	
	FLetsGoMusicNotes CurrentNote = Tonic;
		
	for (FLetsGoMusicScaleStep i : Scale.Steps)
	{
		// Get whole = 2 half = 1
		const int Step = i.Step.GetValue();
			
		// Get next step, wrap around to beginning if >12
		int Next = (CurrentNote.Note.GetValue() + Step) % 12;
			
		// Get the Note enum at position "Next"
		FLetsGoMusicNotes NextNote = FLetsGoMusicNotes(static_cast<ELetsGoMusicNotes>(Next));
			
		// Add to Scale
		GeneratedScale.Notes.Add(NextNote);
			
		// Update CurrentNote for next iteration
		CurrentNote = NextNote;
	}

	return GeneratedScale;
}

TArray<FLetsGoGeneratedScale> ULetsGoMusicEngine::GenerateAllScales(const FLetsGoMusicNotes& Tonic)
{
	TArray<FLetsGoGeneratedScale> AllGeneratedScales;

	for (int i = 0; i < AllScales.Num(); i++ )
	{
		FLetsGoMusicScale thisScale = AllScales[i];
		FLetsGoGeneratedScale generatedScale = GenerateScale(AllScales[i], Tonic);
		AllGeneratedScales.Add(generatedScale);
	}
	
	return AllGeneratedScales;
}
