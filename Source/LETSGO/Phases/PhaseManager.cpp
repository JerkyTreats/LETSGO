// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseManager.h"

#include "SetTonic.h"

UPhaseManager::UPhaseManager()
{
	Phases = TArray<IPhaseController*>();
}

bool UPhaseManager::IsTickable() const
{
	return TickEnabled;
}

void UPhaseManager::Initialize()
{
	USetTonic* SetTonic = NewObject<USetTonic>();
	
	Phases.Emplace(SetTonic);

	TickEnabled = true;

}

void UPhaseManager::ProcessPhases()
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
	if ( ! Phases[0]->IsActivated())
	{
		Phases[0]->Activate();
	}
}

void UPhaseManager::Tick(float DeltaTime)
{
	if (LastFrameNumberWeTicked == GFrameCounter)
		return;

	ProcessPhases();
	
	LastFrameNumberWeTicked = GFrameCounter;
}

