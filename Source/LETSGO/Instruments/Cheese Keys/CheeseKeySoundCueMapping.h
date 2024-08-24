// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheeseKeyData.h"
#include "MetasoundSource.h"
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
	UMetaSoundSource* C1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* CSharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* D1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* DSharp1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* E1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* F1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* FSharp1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* G1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* GSharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* A1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* ASharp1_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* B1_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* C2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* CSharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* D2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* DSharp2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* E2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* F2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* FSharp2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* G2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* GSharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* A2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* ASharp2_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* B2_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* C3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* CSharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* D3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* DSharp3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* E3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* F3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* FSharp3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* G3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* GSharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* A3_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* ASharp3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* B3_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* C4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* CSharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* D4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* DSharp4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* E4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* F4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* FSharp4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* G4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* GSharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* A4_Music_Note;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* ASharp4_Music_Note;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UMetaSoundSource* B4_Music_Note;

	UPROPERTY()
	TArray<UMetaSoundSource*> Notes;

	UPROPERTY()
	TArray<FCheeseKeyData> NoteData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
