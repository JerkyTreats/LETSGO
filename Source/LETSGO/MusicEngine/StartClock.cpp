// Fill out your copyright notice in the Description page of Project Settings.


#include "StartClock.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AStartClock::AStartClock(): Clock(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AStartClock::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStartClock::Initialize()
{
	/** Gets a reference from the Quartz subsystem from the world. */
	UQuartzSubsystem* Quartz = GetWorld()->GetSubsystem<UQuartzSubsystem>();

	FQuartzClockSettings ClockSettings;
	ClockSettings.TimeSignature = TimeSignature;

	/** Creates a new clock the previous setting structures. */
	Clock = Quartz->CreateNewClock(this, ClockName, ClockSettings, true);
	/** Sets the tempo for the clock. */
	Clock->SetBeatsPerMinute(this, FQuartzQuantizationBoundary(), FOnQuartzCommandEventBP(), Clock, BeatsPerMinute);

	// Send Clock to GameMode state object
	ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetMainClock(Clock);
}

void AStartClock::Activate()
{
	IsActive = true;
	
	Clock->StartClock(GetWorld(), Clock);
	Complete();
}

bool AStartClock::IsActivated()
{
	return IsActive;
}

void AStartClock::Deactivate()
{
	IsActive = false;
}

// Not expecting this phase to end?
void AStartClock::Complete()
{
	IsComplete = true;
	Deactivate();
}

// Not expecting this phase to end?
bool AStartClock::IsCompleted()
{
	return IsComplete;
}

void AStartClock::InitiateDestroy()
{
	Destroy();
}

// Called every frame
void AStartClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

