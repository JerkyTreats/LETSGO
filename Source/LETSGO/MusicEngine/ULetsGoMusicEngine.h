// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/LETSGO.h"
#include "ULetsGoMusicEngine.generated.h"

const FString LetsGoBlueprintCategory = FString("LetsGo Music Theory");

UENUM(BlueprintType, Category = LetsGoBlueprintCategory)
enum class ELetsGoMusicScales : uint8 {
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

// For now we are only concerned with 12TET traditional western music
// Named by circle of fifths chart. Not A#, Bb. Notation is bonkers.
// This is an ordered list. That might have consequences down the road.
UENUM(BlueprintType, Category = LetsGoBlueprintCategory)
enum ELetsGoMusicNotes : uint8 {
	C		UMETA(DisplayName = "C"),
	CSharp	UMETA(DisplayName = "C♯"),
	D		UMETA(DisplayName = "D"),
	EFlat	UMETA(DisplayName = "E♭"),
	E		UMETA(DisplayName = "E"),
	F		UMETA(DisplayName = "F"),
	FSharp	UMETA(DisplayName = "F♯"),
	G		UMETA(DisplayName = "G"),
	AFlat	UMETA(DisplayName = "A♭"),
	A		UMETA(DisplayName = "A"),
	BFlat	UMETA(DisplayName = "B♭"),
	B		UMETA(DisplayName = "B"),
};

USTRUCT(BlueprintType, Category = LetsGoBlueprintCategory)
struct FLetsGoMusicNotes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ELetsGoMusicNotes> Note;

	FLetsGoMusicNotes(): Note() {}
	explicit FLetsGoMusicNotes(const ELetsGoMusicNotes Note) : Note(Note) {}
};

// Scales consist of a pattern of 7 whole/half steps.
// C -> D = Whole
// C -> C# = Half 
UENUM(BlueprintType, Category = LetsGoBlueprintCategory)
enum ELetsGoMusicScaleSteps : uint8 {
	Rest = 0,
	Half = 1,
	Whole = 2
};


USTRUCT(BlueprintType, Category = LetsGoBlueprintCategory)
struct FLetsGoMusicScaleStep {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ELetsGoMusicScaleSteps> Step;
};

// Establishes the shape of a scale
// ex. "Ionian" with step pattern "W W H W W W H"
USTRUCT(BlueprintType, Category = LetsGoBlueprintCategory)
struct FLetsGoMusicScale {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLetsGoMusicScaleStep> Steps;

	FLetsGoMusicScale() : Name(TEXT("")), Steps() {}

	FLetsGoMusicScale(const FString& ModeName, const TArray<FLetsGoMusicScaleStep>& ModeSteps) : Name(ModeName), Steps(ModeSteps) {}
};

// Generate a scale given a scales step pattern
// (Scale) + (Tonic) = (Notes)
// "Ionian" + "C" = "{ C, D, E, F, G, A, B }"
USTRUCT(BlueprintType, Category = LetsGoBlueprintCategory)
struct FLetsGoGeneratedScale
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLetsGoMusicNotes Tonic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLetsGoMusicNotes> Notes;

	FLetsGoGeneratedScale() {}

	FLetsGoGeneratedScale(const TArray<FLetsGoMusicNotes>& InNotes)
	{
		if (InNotes.Num() == 0)
		{
			UE_LOG(LogLetsgo, Error, TEXT("FLetsGoGeneratedScale constructed with 0 sized Note array"))
			FLetsGoGeneratedScale();
		} else
		{
			Notes = InNotes;
			Tonic = Notes[0];
		}
	}

	FLetsGoGeneratedScale(const FLetsGoMusicNotes& Tonic, const FLetsGoMusicScale& Scale) : Tonic(Tonic)
	{
		GenerateScale(Tonic, Scale);
	}

	void GenerateScale(const FLetsGoMusicNotes& Tonic, const FLetsGoMusicScale& Scale);
};

/**
 * 
 */
UCLASS()
class LETSGO_API ULetsGoMusicEngine : public UObject
{
	GENERATED_BODY()
	
public:
	ULetsGoMusicEngine();
	virtual ~ULetsGoMusicEngine() override;
	
	static const FLetsGoMusicScale Ionian;
	static const FLetsGoMusicScale Dorian;
	static const FLetsGoMusicScale Phrygian;
	static const FLetsGoMusicScale Lydian;
	static const FLetsGoMusicScale Mixolydian;
	static const FLetsGoMusicScale Aeolian;
	static const FLetsGoMusicScale Locrian;
	// static const FLetsGoMusicScale Pentatonic;
	static const FLetsGoMusicScale Chromatic;
	static const FLetsGoMusicScale WholeStep;
	
	UFUNCTION(BlueprintPure, Category = LetsGoBlueprintCategory)
	static FLetsGoMusicScale GetScale(const ELetsGoMusicScales Scale);

	UFUNCTION(BlueprintPure, Category= LetsGoBlueprintCategory)
	static FLetsGoMusicNotes GetNote(const ELetsGoMusicNotes Note);

	UFUNCTION(BlueprintCallable, Category= LetsGoBlueprintCategory)
	static FLetsGoGeneratedScale GenerateScale(const FLetsGoMusicScale& Scale, const FLetsGoMusicNotes& Tonic);

	UFUNCTION(BlueprintCallable, Category= LetsGoBlueprintCategory)
	static TArray<FLetsGoGeneratedScale> GenerateAllScales(const FLetsGoMusicNotes& Tonic);

	/// Given an Interval ("3rd"), retrieve the possible indices for that Interval in a Chromatic Scale
	/// @param DesiredInterval int of the degree of the scale 
	/// @return Array of possible chromatic scale indices for desired Interval
	UFUNCTION(BlueprintCallable, Category= LetsGoBlueprintCategory)
	static TArray<int> GetInterval(const int DesiredInterval);
};
