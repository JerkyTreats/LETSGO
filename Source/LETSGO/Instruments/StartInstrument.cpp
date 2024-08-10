// Fill out your copyright notice in the Description page of Project Settings.


#include "StartInstrument.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"
#include "LETSGO/Instruments/InstrumentSchedule.h"


// Sets default values
AStartInstrument::AStartInstrument()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<AInstrument>(TEXT("Drums"));
}

// Called when the game starts or when spawned
void AStartInstrument::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStartInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FInstrumentSchedule GenerateInstrumentSchedule()
{
	const TArray BaseFloats = {1.0f, 3.0f};
	const TArray FourFloats = {1.0f,2.0f,3.0f,4.0f};
	FPerBarSchedule BasePattern = FPerBarSchedule(BaseFloats);
	FPerBarSchedule FourFloor = FPerBarSchedule(FourFloats);
	FInstrumentSchedule DrumPattern = FInstrumentSchedule(EQuartzCommandQuantization::Beat);

	for (int i = 0; i < 3; i++)
	{
		DrumPattern.BeatSchedule.Emplace(BasePattern);
	}
	DrumPattern.BeatSchedule.Emplace(FourFloats);

	return DrumPattern;
}

void AStartInstrument::Initialize()
{
	const FInstrumentSchedule DrumPattern = GenerateInstrumentSchedule();
	
	Drums = GetWorld()->SpawnActorDeferred<AInstrument>(AInstrumentClass, FTransform());
	Drums->Initialize(DrumPattern);
	Drums->FinishSpawning(FTransform());
	
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	InstrumentRack = GameMode->GetInstrumentRack();
	InstrumentRack->AddInstrument(Drums);
}


void AStartInstrument::Activate()
{
	UE_LOG(LogTemp, Display, TEXT("Phase StartDrums Activated"))
	Drums->StartPlaying();
	IsComplete = true;
}

bool AStartInstrument::IsActivated()
{
	return IsActive;
}

void AStartInstrument::Deactivate()
{
}

void AStartInstrument::Complete()
{
	InitiateDestroy();
}

bool AStartInstrument::IsCompleted()
{
	return IsComplete;
}

void AStartInstrument::InitiateDestroy()
{
	Destroy();
}

