// Fill out your copyright notice in the Description page of Project Settings.


#include "Drums.h"

#include "Components/AudioComponent.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
ADrums::ADrums(): Clock(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstrumentAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	InstrumentAudioComponent->SetAutoActivate(false);
	InstrumentAudioComponent->SetSound(InstrumentMetaSoundSource);
}

// Called when the game starts or when spawned
void ADrums::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Setting Drum MainClock from GameMode clock object"));
	// Get Main Clock
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	Clock = GameMode->GetMainClock();
}

// Called every frame
void ADrums::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

