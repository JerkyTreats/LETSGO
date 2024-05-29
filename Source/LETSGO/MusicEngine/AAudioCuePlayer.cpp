// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioCuePlayer.h"
#include "..\GameModes\ALetsGoGameMode.h"


AAudioCuePlayer::AAudioCuePlayer()
{	

}

void AAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Clock = GameMode->GetMainClock();

	
}
