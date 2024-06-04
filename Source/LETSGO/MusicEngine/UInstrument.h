// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "UInstrument.generated.h"


UCLASS(ClassGroup=(LETSGO), meta=(BlueprintSpawnableComponent))
class LETSGO_API UInstrument : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInstrument();

	UPROPERTY(VisibleAnywhere, Category = "LETSGO | State")  
	UQuartzClockHandle* Clock; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category="LetsGo | Instrument")
	UQuartzClockHandle* GetClock () const;
};
