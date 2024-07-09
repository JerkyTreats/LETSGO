// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"

#include "SetTonic.h"

UPhaseManager::UPhaseManager()
{
	Phases = TArray<IPhaseController*>();
}

void UPhaseManager::Initialize()
{
	USetTonic* SetTonic = NewObject<USetTonic>();
	
	Phases.Emplace(SetTonic);
}

void UPhaseManager::ProcessPhases()
{
	
}
