// Fill out your copyright notice in the Description page of Project Settings.


#include "LetsGoGameMode.h"

#include "LetsGoGameState.h"


ALetsGoGameMode::ALetsGoGameMode()
{
	GameStateClass = ALetsGoGameState::StaticClass();
}

UQuartzClockHandle& ALetsGoGameMode::GetMainClock()
{
	return GetGameState<ALetsGoGameState>()->MainClock;
}

void ALetsGoGameMode::SetMainClock(UQuartzClockHandle* Clock)
{
	GetGameState<ALetsGoGameState>()->MainClock = *Clock;
}

// Audio::FQuartzClock ALetsGoGameMode::GetMainClock() const
// {
// 	Audio::FQuartzClockProxy Proxy = GetGameState<ALetsGoGameState>()->Clock;
// 	
// }
//
// void ALetsGoGameMode::SetMainClock(Audio::FQuartzClockProxy newClock)
// {
// 	GetGameState<ALetsGoGameState>()->Clock = newClock;
// }
