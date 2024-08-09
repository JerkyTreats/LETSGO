// Fill out your copyright notice in the Description page of Project Settings.


#include "StartDrums.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"


// Sets default values
AStartDrums::AStartDrums()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<ADrums>(TEXT("Drums"));
}

// Called when the game starts or when spawned
void AStartDrums::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStartDrums::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FInstrumentSchedule GenerateInstrumentSchedule()
{
	const TArray BaseFloats = {1.0f, 3.0f};
	const TArray FourFloats = {1.0f,2.0f,3.0f,4.0f};
	FPerBarSchedule BasePattern = FPerBarSchedule(BaseFloats);
	FPerBarSchedule FourFloor = FPerBarSchedule(FourFloats);
	FInstrumentSchedule DrumPattern = FInstrumentSchedule();

	for (int i = 0; i < 3; i++)
	{
		DrumPattern.BeatSchedule.Emplace(BasePattern);
	}
	DrumPattern.BeatSchedule.Emplace(FourFloats);

	return DrumPattern;
}

void AStartDrums::Initialize()
{
	const FInstrumentSchedule DrumPattern = GenerateInstrumentSchedule();
	
	Drums = GetWorld()->SpawnActorDeferred<ADrums>(ADrumsClass, FTransform());
	Drums->Initialize(DrumPattern);
	Drums->FinishSpawning(FTransform());
	
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	InstrumentRack = GameMode->GetInstrumentRack();
	InstrumentRack->AddInstrument(Drums);
}


void AStartDrums::Activate()
{
	UE_LOG(LogTemp, Display, TEXT("Phase StartDrums Activated"))
	Drums->StartPlaying();
	IsComplete = true;
}

bool AStartDrums::IsActivated()
{
	return IsActive;
}

void AStartDrums::Deactivate()
{
}

void AStartDrums::Complete()
{
	InitiateDestroy();
}

bool AStartDrums::IsCompleted()
{
	return IsComplete;
}

void AStartDrums::InitiateDestroy()
{
	Destroy();
}

