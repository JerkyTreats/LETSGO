﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"

#include "SetTonic.h"

APhaseManager::APhaseManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Phases = TArray<IPhaseController*>();
	SetTonic = CreateDefaultSubobject<ASetTonic>(TEXT("Set Tonic"));
}

void APhaseManager::BeginPlay()
{
	Super::BeginPlay();

	SetTonic = GetWorld()->SpawnActor<ASetTonic>(SetTonicClass);
	Phases.Emplace(SetTonic);

}

void APhaseManager::Initialize()
{
	SetTonic->Initialize();
	TickEnabled = true;
}

void APhaseManager::ProcessPhases()
{

	
	if (Phases.Num() == 0)
	{
		if (EmptyListWarnAmount < 5)
		{
			// TODO create custom Log Category 
			UE_LOG(LogTemp, Warning, TEXT("Empty Phase List"));
			EmptyListWarnAmount++;
			
			if (EmptyListWarnAmount == 5 )
			{
				UE_LOG(LogTemp, Warning, TEXT("Disabling Empty Phase List Warning."));
			}
		}
		return;
	}
	
	EmptyListWarnAmount = 0;

	if (Phases[0]->IsCompleted())
	{
		Phases.RemoveAt(0);
	}

	if (Phases.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Last Phase In Phase List Completed"));
		return;
	}

	// Activate next phase
	if ( Phases.Num() > 0 && ! Phases[0]->IsActivated())
	{
		Phases[0]->Activate();
	}
}

void APhaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TickEnabled)
	{
		ProcessPhases();
	}
}


