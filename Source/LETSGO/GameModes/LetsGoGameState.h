// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Quartz/AudioMixerClock.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "LetsGoGameState.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API ALetsGoGameState : public AGameState
{
	GENERATED_BODY()

public:
	ALetsGoGameState();
	virtual ~ALetsGoGameState() override;
	
	TWeakObjectPtr<UQuartzClockHandle> MainClock;
};
