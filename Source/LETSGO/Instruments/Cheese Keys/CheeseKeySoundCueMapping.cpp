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

	Notes = {
		C1_Music_Note,
		CSharp1_Music_Note,
		D1_Music_Note,
		DSharp1_Music_Note,
		E1_Music_Note,
		F1_Music_Note,
		FSharp1_Music_Note,
		G1_Music_Note,
		GSharp1_Music_Note,
		A1_Music_Note,
		ASharp1_Music_Note,
		B1_Music_Note,
		C2_Music_Note,
		CSharp2_Music_Note,
		D2_Music_Note,
		DSharp2_Music_Note,
		E2_Music_Note,
		F2_Music_Note,
		FSharp2_Music_Note,
		G2_Music_Note,
		GSharp2_Music_Note,
		A2_Music_Note,
		ASharp2_Music_Note,
		B2_Music_Note,
		C3_Music_Note,
		CSharp3_Music_Note,
		D3_Music_Note,
		DSharp3_Music_Note,
		E3_Music_Note,
		F3_Music_Note,
		FSharp3_Music_Note,
		G3_Music_Note,
		GSharp3_Music_Note,
		A3_Music_Note,
		ASharp3_Music_Note,
		B3_Music_Note,
		C4_Music_Note,
		CSharp4_Music_Note,
		D4_Music_Note,
		DSharp4_Music_Note,
		E4_Music_Note,
		F4_Music_Note,
		FSharp4_Music_Note,
		G4_Music_Note,
		GSharp4_Music_Note,
		A4_Music_Note,
		ASharp4_Music_Note,
		B4_Music_Note,
	};
	
	NoteData = FInstrumentNote::GenerateKeys(Notes);
}

// Called every frame
void ACheeseKeySoundCueMapping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

