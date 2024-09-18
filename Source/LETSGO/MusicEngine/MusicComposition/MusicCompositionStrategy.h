// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicComposer.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"
#include "UObject/Interface.h"
#include "MusicCompositionStrategy.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMusicCompositionStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LETSGO_API IMusicCompositionStrategy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FInstrumentSchedule Apply(const FComposerData& Data) = 0;
};
