// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LETSGO/Instruments/InstrumentRack.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "Quartz/AudioMixerClock.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "ALetsGoGameState.generated.h"

class UQuartzClockHandle;

/**
 * 
 */
UCLASS()
class LETSGO_API ALetsGoGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALetsGoGameState();
	virtual ~ALetsGoGameState() override;
	
	UPROPERTY(VisibleAnywhere, Category = "LETSGO")  
	TObjectPtr<UQuartzClockHandle> MainClock;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Tonic;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	UInstrumentRack* InstrumentRack;
};
