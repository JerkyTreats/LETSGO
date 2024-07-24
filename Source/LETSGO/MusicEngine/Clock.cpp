// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"

#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AClock::AClock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClock::Initialize()
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

void AClock::Activate()
{
	Clock->StartClock(GetWorld(), Clock);
	IsActive = true;
}

bool AClock::IsActivated()
{
	return IsActive;
}

void AClock::Deactivate()
{
	// Note CancelPendingEvents is false here, unsure of consequences
	Clock ->StopClock(GetWorld(), false,Clock);
	IsActive = false;
}

// Not expecting this phase to end?
void AClock::Complete()
{
}

// Not expecting this phase to end?
bool AClock::IsCompleted()
{
	return false;
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

