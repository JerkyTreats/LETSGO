// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "NiagaraComponent.h"
#include "AudioPlatform.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LETSGO_API UAudioPlatform : public UObject
{
	GENERATED_BODY()

public:
	UAudioPlatform();

	void TriggerAudioNote(FLetsGoMusicNotes Note);
	// void Destruct(const TArray<UNiagaraComponent>& MusicParticleSystem);
};
