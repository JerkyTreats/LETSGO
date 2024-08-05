// Fill out your copyright notice in the Description page of Project Settings.


#include "StartDrums.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"


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

void AStartDrums::Initialize()
{
	Drums = GetWorld()->SpawnActor<ADrums>(ADrumsClass);
	
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

