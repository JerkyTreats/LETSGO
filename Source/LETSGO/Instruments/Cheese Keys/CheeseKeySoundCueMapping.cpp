// Fill out your copyright notice in the Description page of Project Settings.


#include "CheeseKeySoundCueMapping.h"


// Sets default values
ACheeseKeySoundCueMapping::ACheeseKeySoundCueMapping()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACheeseKeySoundCueMapping::BeginPlay()
{
	Super::BeginPlay();
	NoteData = FCheeseKeyData::GenerateKeys(Notes);
}

// Called every frame
void ACheeseKeySoundCueMapping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

