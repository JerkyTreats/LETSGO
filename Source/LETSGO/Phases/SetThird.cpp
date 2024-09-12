// Fill out your copyright notice in the Description page of Project Settings.


#include "SetThird.h"

#include "DSP/MidiNoteQuantizer.h"


// Sets default values
ASetThird::ASetThird()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASetThird::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetThird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASetThird::Activate()
{
}

bool ASetThird::IsActivated()
{
	return false; //temp
}

void ASetThird::Deactivate()
{
}

void ASetThird::Complete()
{
}

bool ASetThird::IsCompleted()
{
	return false; // temp
}

void ASetThird::InitiateDestroy()
{
}

