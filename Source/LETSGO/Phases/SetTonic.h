// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhaseController.h"
#include "UObject/Object.h"
#include "SetTonic.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API USetTonic : public UObject, public IPhaseController
{
	GENERATED_BODY()

	virtual void Initialize() override;
	virtual void Activate() override;
	virtual void Deactivate() override;

private:
	bool Active = false; 
};
