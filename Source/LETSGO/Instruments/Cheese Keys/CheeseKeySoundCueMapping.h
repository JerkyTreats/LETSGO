// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheeseKeyData.h"
#include "MetasoundSource.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Instruments/InstrumentNote.h"
#include "Sound/SoundCue.h"
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
	USoundCue* C1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* CSharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* D1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* DSharp1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* E1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* F1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* FSharp1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* G1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* GSharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* A1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* ASharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* B1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* C2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* CSharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* D2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* DSharp2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* E2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* F2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* FSharp2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* G2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* GSharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* A2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* ASharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* B2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* C3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* CSharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* D3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* DSharp3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* E3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* F3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* FSharp3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* G3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* GSharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* A3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* ASharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* B3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* C4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* CSharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* D4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* DSharp4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* E4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* F4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* FSharp4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* G4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* GSharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* A4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* ASharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundCue* B4_Music_Note;

	UPROPERTY()
	TArray<USoundCue*> Notes;

	UPROPERTY()
	TArray<FCheeseKeyData> NoteData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
