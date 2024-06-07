// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UAudioCuePlayer.h"
#include "ULetsGoMusicEngine.h"
#include "UParticleController.h"
#include "UObject/Object.h"
#include "AAudioPlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAudioPlatformTriggerDelegate, FLetsGoMusicNotes, Note);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAudioPlatformInitializedDelegate);
/**
 * 
 */
UCLASS(Blueprintable)
class LETSGO_API AAudioPlatform : public AActor
{
	GENERATED_BODY()

public:
	AAudioPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	FLetsGoMusicNotes Note;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO | AudioPlatform")
	FAudioPlatformTriggerDelegate OnAudioPlatformTriggered;

	UPROPERTY(EditDefaultsOnly, Blueprintable)
	class UAudioCuePlayer* AudioCuePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Blueprintable)
	UParticleController* ParticleController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	float ActorDestroyDelay;


	UFUNCTION(BlueprintCallable)
	void InitializeAudioPlatform(FLetsGoMusicNotes MusicNote, UStaticMeshComponent* Mesh, const FQuartzQuantizationBoundary& QuartzQuantizationBoundary);
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "LETSGO | AudioPlatform")
	FAudioPlatformInitializedDelegate OnAudioPlatformInitialized;


	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY()
	bool AudioPlatform_ReadyForCleanup = false;

	UPROPERTY()
	bool AudioCuePlayer_Destroyed = false;

	UPROPERTY()
	bool ParticleController_Destroyed = false;

	UFUNCTION()
	void OnAudioCuePlatformReadyForCleanup();
	
	UFUNCTION()
	void OnParticleControllerReadyForCleanup();

	UFUNCTION()
	void PreDestroy();
	
	UFUNCTION()
	void PostDestroy();
	
	virtual void BeginPlay() override;
};
