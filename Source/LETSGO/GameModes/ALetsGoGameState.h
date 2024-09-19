﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LETSGO/Instruments/InstrumentRack.h"
#include "LETSGO/Instruments/Cheese Keys/CheeseKeySoundCueMapping.h"
#include "LETSGO/MusicEngine/ClockSettings.h"
#include "LETSGO/MusicEngine/ULetsGoMusicEngine.h"
#include "LETSGO/MusicEngine/MusicComposition/MusicComposer.h"
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
	AClockSettings* ClockSettings;

	// Generated Notes 
	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Tonic;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Second;
	
	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Third;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Fourth;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Fifth;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Sixth;

	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	FLetsGoMusicNotes Seventh;

	
	UPROPERTY(VisibleAnywhere, Category= "LETSGO")
	UInstrumentRack* InstrumentRack;

	UPROPERTY(VisibleAnywhere, Category="LETSGO")
	ACheeseKeySoundCueMapping* InstrumentData_CheeseKey;

	UPROPERTY(VisibleAnywhere, Category="LETSGO")
	AMusicComposer* MusicComposer;
};
