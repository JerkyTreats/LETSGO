// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategy_Rest.h"

#include "ComposerData.h"
#include "MusicComposerState.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"

FInstrumentSchedule UStrategy_Rest::GenerateInstrumentSchedule(FComposerData& CurrentComposerData, const AMusicComposerState* State, const int StartAtBar)
{
	
	return FInstrumentSchedule();
}

float UStrategy_Rest::GetStrategyAppropriateness(FComposerData& CurrentComposerData, const AMusicComposerState* State)
{
	if (! CurrentComposerData.IsMultiNoteInstrument() || State->AllowableNoteIndices.Num() == 0)
	{
		return 1.0f;
	}

	float Weight = 0.3f;
	
	return Weight;
}

// This strategy doesn't need input from other instruments
float UStrategy_Rest::GetInstrumentAppropriateness(FComposerData& CurrentComposerData,
	const AMusicComposerState* State)
{
	return 0.0f;
}

