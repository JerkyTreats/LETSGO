﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicComposer.h"

#include "Strategy_PedalPointComposition.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AMusicComposer::AMusicComposer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMusicComposer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicComposer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMusicComposer::Initialize()
{
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnMusicalStateUpdated.AddDynamic(this, &AMusicComposer::GenerateScale);
}

void AMusicComposer::GenerateScale()
{
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	const FLetsGoMusicNotes Tonic = GameMode->GetTonic();
	const FLetsGoMusicNotes Second = GameMode->GetSecond();
	const FLetsGoMusicNotes Third = GameMode->GetThird();
	const FLetsGoMusicNotes Fourth = GameMode->GetFourth();
	const FLetsGoMusicNotes Fifth = GameMode->GetFifth();
	const FLetsGoMusicNotes Sixth = GameMode->GetSixth();
	const FLetsGoMusicNotes Seventh = GameMode->GetSeventh();

	const TArray<FLetsGoMusicNotes> Notes {
		Tonic,
		Second,
		Third,
		Fourth,
		Fifth,
		Sixth,
		Seventh
	};
	
	Scale = FLetsGoGeneratedScale();
	Scale.Notes = Notes;
	Scale.Tonic = Tonic;
	Scale.IsValid = true;
}

void AMusicComposer::AddComposerData(FComposerData NewDataObject)
{
	if (NewDataObject.ComposerDataObjectIndex)
	{
		UE_LOG(LogLetsgo, Error, TEXT("AddComposerData called with ComposerData index. Consider MergeComposerData instead."))
		return;
	}
	
	NewDataObject.ComposerDataObjectIndex = ComposerDataObjects.Num();

	NewDataObject.Scale = (NewDataObject.Scale.IsValid) ? NewDataObject.Scale : Scale;
	
	ComposerDataObjects.Emplace(NewDataObject);
}

void AMusicComposer::MergeComposerData(FComposerData NewDataObject)
{
	if (! NewDataObject.ComposerDataObjectIndex)
	{
		UE_LOG(LogLetsgo, Error, TEXT("MergeComposerData called with null index. Consider AddComposerData instead."))
		return;
	}
	
	FComposerData Base = ComposerDataObjects[NewDataObject.ComposerDataObjectIndex];

	// This is either some jank-ass shit or utter brilliance. I know which I would bet on.
	Base.NumBarsToCompose	= (NewDataObject.NumBarsToCompose)	? NewDataObject.NumBarsToCompose	: Base.NumBarsToCompose;
	Base.Scale				= (NewDataObject.Scale.IsValid)		? NewDataObject.Scale				: Base.Scale;
	Base.OctaveMin			= (NewDataObject.OctaveMin)			? NewDataObject.OctaveMin			: Base.OctaveMin;
	Base.OctaveMax			= (NewDataObject.OctaveMax)			? NewDataObject.OctaveMax			: Base.OctaveMax;
	Base.InstrumentScheduleInput = (NewDataObject.InstrumentScheduleInput.IsValid) ?  NewDataObject.InstrumentScheduleInput : Base.InstrumentScheduleInput;
	Base.CompositionStrategy = (NewDataObject.CompositionStrategy) ? NewDataObject.CompositionStrategy : Base.CompositionStrategy;
	
}

void AMusicComposer::ChooseMusicalStrategy()
{
}

FInstrumentSchedule AMusicComposer::ComposeInstrumentSchedule()
{
	return FInstrumentSchedule();
}
