// Fill out your copyright notice in the Description page of Project Settings.


#include "SongSection.h"

#include "Strategy_CreateMotif.h"
#include "Strategy_PedalPointComposition.h"

void FSongSection::GenerateInstrumentPlans(TArray<TEnumAsByte<EInstrumentRoles>> InstrumentRoles)
{
	for (int i = 0; i < InstrumentRoles.Num(); i++)
	{
		FSectionInstrumentPlan InstrumentPlan = FSectionInstrumentPlan();
		InstrumentPlan.InstrumentRole = InstrumentRoles[i];
		GeneratedPlans.Emplace(InstrumentPlan);
	}
}

void FSongSections::InitializeSongSections()
{
	//Intro
	FSongSection Intro = FSongSection(ESongSection::Intro);
	Intro.CandidateStrategies.Emplace(FSectionStrategy(PedalPoint, 0.5f));
	Intro.CandidateStrategies.Emplace(FSectionStrategy(CreateMotif, 0.5f));
	
	CandidateSections.Emplace(Intro);
}

void FSongSections::GenerateSongSections()
{
	if (GeneratedSections.Num() == 0)
	{
		GeneratedSections.Emplace(CandidateSections[0]);
		GeneratedSections[0].GenerateInstrumentPlans(InstrumentRoles);
	}

	while (GeneratedSections.Num() <= DesiredSectionsAmount)
	{
		GenerateNextSongSection();
	}
}

void FSongSections::GenerateNextSongSection()
{
	FSongSection NextSection = GeneratedSections.Last();

	for (int i = 0; i < CandidateSections.Num(); i++)
	{
		
	}
}
