// Fill out your copyright notice in the Description page of Project Settings.


#include "MainClock.h"

#include "Quartz/QuartzSubsystem.h"


// Sets default values
AMainClock::AMainClock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainClock::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMainClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

