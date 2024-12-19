// Fill out your copyright notice in the Description page of Project Settings.


#include "SongSection.h"

#include "Strategy_CreateMotif.h"
#include "Strategy_PedalPointComposition.h"

FSongSections FSongSections::InitializeSongSections()
{
	// Intro
	FSectionStrategy PedalPoint = FSectionStrategy(
		NewObject<UStrategy_PedalPointComposition>(),
		0.5f
	);
	FSectionStrategy CreateMotif = FSectionStrategy(
		NewObject<UStrategy_CreateMotif>(),
		0.5f
	);
	
	FSongSections ToReturn = FSongSections();
	ToReturn.SongSections = {
		FSongSection(ESongSection::Intro, {PedalPoint}), 
		FSongSection(ESongSection::Outro, {PedalPoint}),
		FSongSection(ESongSection::Refrain, {CreateMotif}), //RepeatMotif, 
		FSongSection(ESongSection::Episode, {CreateMotif}), //EvolveMotif, RepeatMotif
		FSongSection(ESongSection::Bridge, {CreateMotif}) // RepeatMotif
	};
	return ToReturn;
}
