// Fill out your copyright notice in the Description page of Project Settings.


#include "UParticleController.h"

#include "AAudioPlatform.h"


// Sets default values for this component's properties
UParticleController::UParticleController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParticleController::BeginPlay()
{
	Super::BeginPlay();

	AudioPlatformReference = Cast<AAudioPlatform>(GetOwner());
	// AudioPlatformReference->OnAudioPlatformInitialized.AddDynamic(this, )
}


// Called every frame
void UParticleController::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParticleController::ReadyForCleanup()
{
	OnReadyForCleanUp.Broadcast();
}

