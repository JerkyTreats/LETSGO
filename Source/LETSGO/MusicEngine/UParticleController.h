// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "Components/ActorComponent.h"
#include "UParticleController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReadyForCleanUpDelegate);

UCLASS(Blueprintable, ClassGroup=(LETSGO), meta=(BlueprintSpawnableComponent))
class LETSGO_API UParticleController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UParticleController();

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO")
	FOnReadyForCleanUpDelegate OnReadyForCleanUp;

	UPROPERTY(BlueprintReadWrite)
	FLetsGoMusicNotes Note;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite)
	class AAudioPlatform* AudioPlatformReference;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// virtual void OnComponentCreated() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReadyForCleanup();
};
