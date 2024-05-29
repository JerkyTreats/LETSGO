// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "AAudioCuePlayer.generated.h"

/**
 * 
 */
UCLASS()
class LETSGO_API AAudioCuePlayer : public AActor
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	AAudioCuePlayer();
	
	UPROPERTY(VisibleAnywhere, Category = "LETSGO | State")  
	UQuartzClockHandle* Clock;
	
	
};

