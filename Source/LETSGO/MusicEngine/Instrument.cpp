// Fill out your copyright notice in the Description page of Project Settings.


#include "Instrument.h"

#include "LETSGO/GameModes/LetsGoGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInstrument::UInstrument(): Clock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInstrument::BeginPlay()
{
	Super::BeginPlay();

	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Clock = GameMode->GetMainClock();
	

}


// Called every frame
void UInstrument::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

