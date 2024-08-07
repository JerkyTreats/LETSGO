// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockSettings.h"

#include "Quartz/QuartzSubsystem.h"


// Sets default values
AClockSettings::AClockSettings()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClockSettings::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClockSettings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * Helper method to create a clock
 * @param ClockName 
 * @return new QuartzClockHandle clock. 
 */
UQuartzClockHandle* AClockSettings::GetNewClock(FName ClockName) const
{
	UQuartzSubsystem* Quartz = GetWorld()->GetSubsystem<UQuartzSubsystem>();

	FQuartzClockSettings NewClockSettings = ClockSettings;
	NewClockSettings.TimeSignature = TimeSignature;

	UQuartzClockHandle* Clock = Quartz->CreateNewClock(this, ClockName, NewClockSettings, true);

	Clock->SetBeatsPerMinute(this, QuartzQuantizationBoundary, FOnQuartzCommandEventBP(), Clock, BeatsPerMinute);

	return Clock;
}

