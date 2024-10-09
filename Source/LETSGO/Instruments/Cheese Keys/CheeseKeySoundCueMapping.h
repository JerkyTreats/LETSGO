// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentNote.h"
#include "CheeseKeySoundCueMapping.generated.h"

UCLASS()
class LETSGO_API ACheeseKeySoundCueMapping : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheeseKeySoundCueMapping();
	
	// Maybe theres a better way to do this, do some lookup mapping at construction time
	// For now we can just manual map these

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* C1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* CSharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* D1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* DSharp1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* E1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* F1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* FSharp1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* G1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* GSharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* A1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* ASharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* B1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* C2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* CSharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* D2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* DSharp2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* E2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* F2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* FSharp2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* G2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* GSharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* A2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* ASharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* B2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* C3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* CSharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* D3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* DSharp3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* E3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* F3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* FSharp3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* G3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* GSharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* A3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* ASharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* B3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* C4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* CSharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* D4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* DSharp4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* E4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* F4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* FSharp4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* G4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* GSharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* A4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* ASharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundWave* B4_Music_Note;

	UPROPERTY()
	TArray<USoundWave*> Notes;

	UPROPERTY()
	FInstrumentData NoteData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
