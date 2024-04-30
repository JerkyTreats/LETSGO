// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "LetsGoGameMode.generated.h"

/**
 * Custom Game Mode for LETSGO.
 *
 * This acts as a Controller in a MVC software design pattern
 * It is intended to facilitate inter-asset communication
 * 
 */
UCLASS()
class LETSGO_API ALetsGoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALetsGoGameMode();

	UFUNCTION(BlueprintPure, Category="LetsGo|Clock")
	UQuartzClockHandle* GetMainClock() const;
	
	UFUNCTION(BlueprintCallable, Category="LetsGo|Clock")
	virtual void SetMainClock(UQuartzClockHandle* Clock);
	
};
