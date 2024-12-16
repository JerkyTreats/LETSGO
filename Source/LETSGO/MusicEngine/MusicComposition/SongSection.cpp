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

	FSongSection Intro = FSongSection(ESongSection::Intro, {PedalPoint, CreateMotif});

	FSongSections ToReturn = FSongSections();
	ToReturn.SongSections = {Intro};
	return ToReturn;
}
