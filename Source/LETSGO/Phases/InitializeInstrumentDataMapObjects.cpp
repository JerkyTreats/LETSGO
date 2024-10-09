// Fill out your copyright notice in the Description page of Project Settings.


#include "InitializeInstrumentDataMapObjects.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AInitializeInstrumentDataMapObjects::AInitializeInstrumentDataMapObjects()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInitializeInstrumentDataMapObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInitializeInstrumentDataMapObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInitializeInstrumentDataMapObjects::Initialize()
{
	ADrumSoundCueMapping* DrumMapping = GetWorld()->SpawnActor<ADrumSoundCueMapping>(ADrumSoundCueMappingClass);
	ACheeseKeySoundCueMapping* CheeseKeyMapping = GetWorld()->SpawnActor<ACheeseKeySoundCueMapping>(CheeseKeyMappingClass);

	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());

	GameMode->SetInstrumentData_Drums(DrumMapping);
	GameMode->SetInstrumentData_CheeseKey(CheeseKeyMapping);

	Destroy();
}
