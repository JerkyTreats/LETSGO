﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PhaseController.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPhaseController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LETSGO_API IPhaseController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Activate() = 0 ;
	virtual bool IsActivated() = 0;
	
	virtual void Deactivate() = 0;
	
	virtual void Complete() = 0;
	virtual bool IsCompleted() = 0;

	virtual void InitiateDestroy() = 0;
};
