// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LETSGO/MusicEngine/MusicComposition/MusicComposer.h"
#include "GameFramework/Actor.h"
#include "LETSGO/Phases/PhaseController.h"
#include "StartMusicComposer.generated.h"

UCLASS()
class LETSGO_API AStartMusicComposer : public AActor, public IPhaseController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStartMusicComposer();

	UPROPERTY()
	AMusicComposer* Composer;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="LETSGO")
	TSubclassOf<AMusicComposer> MusicComposerClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Completed;
	bool Active;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Initialize();
	
	UFUNCTION()
	virtual void Activate() override;
	
	UFUNCTION()
	virtual bool IsActivated() override;

	UFUNCTION()
	virtual void Deactivate() override;

	UFUNCTION()
	virtual void Complete() override;

	UFUNCTION()
	virtual bool IsCompleted() override;

	UFUNCTION()
	virtual void InitiateDestroy() override;
};
