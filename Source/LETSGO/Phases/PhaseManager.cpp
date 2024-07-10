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
	SetTonic->OnPhaseDeactivate.AddDynamic(this, &UPhaseManager::UPhaseManager::DeactivatePhase);
	
	Phases.Emplace(SetTonic);
}

void UPhaseManager::ProcessPhases()
{
	
}

void UPhaseManager::ActivatePhase(IPhaseController* ToActivate)
{
	ToActivate->Activate();
}

void UPhaseManager::DeactivatePhase(IPhaseController* ToDeactivate)
{
	Phases.Remove(ToDeactivate);
	ProcessPhases();
}

void UPhaseManager::RemovePhase(IPhaseController* ToRemove)
{
}

