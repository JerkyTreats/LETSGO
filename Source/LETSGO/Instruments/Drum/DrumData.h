// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "DrumData.generated.h"

// See https://drumhelper.com/learning-drums/common-drum-beats-and-patterns/
UENUM()
enum EDrumPatterns
{
	BasicRock,
	FourOnTheFloor,
	Funk,
	BossaNova,
	Samba,
	Shuffle,
	HalfTimeShuffle,
	DiscoGroove,
	Motown,
	Swing,
	Reggae,
	Pop,
	Country,
	SixteenthNoteGroove
};

USTRUCT()
struct FDrumPattern
{
	GENERATED_BODY()
	
	FInstrumentSchedule Kick;
	FInstrumentSchedule Snare;
	FInstrumentSchedule HiHatClosed;
	FInstrumentSchedule HiHatOpen;
	FInstrumentSchedule Clap;

	FDrumPattern();
};

/**
 * 
 */
class LETSGO_API DrumData
{
public:
	FDrumPattern BasicRock;
	FDrumPattern FourOnTheFloor;
	FDrumPattern Funk;
	FDrumPattern BossaNova;
	FDrumPattern Samba;
	FDrumPattern Shuffle;
	FDrumPattern HalfTimeShuffle;
	FDrumPattern DiscoGroove;
	FDrumPattern Motown;
	FDrumPattern Swing;
	FDrumPattern Reggae;
	FDrumPattern Pop;
	FDrumPattern Country;
	FDrumPattern SixteenthGroove;
	
	DrumData();
	~DrumData();
};
