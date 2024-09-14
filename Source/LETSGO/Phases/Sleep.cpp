// Fill out your copyright notice in the Description page of Project Settings.


#include "Sleep.h"

#include "LETSGO/LETSGO.h"


// Sets default values
ASleep::ASleep()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASleep::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASleep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASleep::Initialize(const float SleepAmount)
{
	SleepTime = SleepAmount;
}

void ASleep::Activate()
{
	Active = true;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASleep::Complete,SleepTime,false);
	UE_LOG(LogLetsgo, Display, TEXT("Sleep Phase Active for [%f] seconds"), SleepTime);
}

bool ASleep::IsActivated()
{
	return Active;
}

void ASleep::Deactivate()
{
	Active = false;
}

void ASleep::Complete()
{
	Completed = true;

	Deactivate();
}

bool ASleep::IsCompleted()
{
	return Completed;
}

void ASleep::InitiateDestroy()
{
	Destroy();
}

