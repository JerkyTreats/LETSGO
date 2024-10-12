// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicConductor.h"


// Sets default values
AMusicConductor::AMusicConductor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMusicConductor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicConductor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

