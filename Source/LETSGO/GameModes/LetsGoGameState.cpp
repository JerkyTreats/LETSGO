// Fill out your copyright notice in the Description page of Project Settings.


#include "LetsGoGameState.h"

ALetsGoGameState::ALetsGoGameState(): MainClock()
{
}

ALetsGoGameState::~ALetsGoGameState()
{
	if (MainClock != nullptr)
	{
		delete MainClock; // Deallocate memory for MainClock
		MainClock = nullptr;
	}
}

// FQuartzClock(const FName& InName,
// const FQuartzClockSettings& InClockSettings,
// FQuartzClockManager*
// InOwningClockManagerPtr = nullptr);
