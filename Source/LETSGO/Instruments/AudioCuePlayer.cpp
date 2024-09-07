// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioCuePlayer.h"

#include "AsyncTreeDifferences.h"
#include "Components/AudioComponent.h"


// Sets default values
AAudioCuePlayer::AAudioCuePlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Attached Audio Component"));
	SetRootComponent(AudioComponent);
	AudioComponent->SetAutoActivate(false); // Don't play immediately
	AudioComponent->bAllowSpatialization = false; // Don't play in world
}

// Called when the game starts or when spawned
void AAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAudioCuePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAudioCuePlayer::Initialize(const FMetaSoundPlayerData& MetaSoundData, UQuartzClockHandle* ParentClock,
                                 const FQuartzQuantizationBoundary& ParentQuartzQuantizationBoundary)
{
	Clock = ParentClock;
	QuartzQuantizationBoundary = ParentQuartzQuantizationBoundary;

	SoundPlayerData = MetaSoundData;
	AudioComponent->SetSound(MetaSoundPlayer);
	AudioComponent->Activate();
	InitializeMetaSoundPlayer();

}

void AAudioCuePlayer::InitializeMetaSoundPlayer() 
{

	
	/*
	TArray<FAudioParameter> SoundParams = {
		FAudioParameter(SoundPlayerData.WaveAssetName, SoundPlayerData.WaveAsset),
		FAudioParameter(SoundPlayerData.OutputVolumeName, SoundPlayerData.OutputVolume),
	};
	MetaSoundPlayer->InitParameters(SoundParams, FName());


	TArray<FAudioParameter> ParamsCopy = AudioComponent->DefaultParameters;
	FAudioParameter::Merge(MoveTemp(ParamsCopy), SoundParams);

	AudioComponent->DefaultParameters = SoundParams;
	*/
	
	AudioComponent->SetWaveParameter(SoundPlayerData.WaveAssetName, SoundPlayerData.WaveAsset);
	AudioComponent->SetFloatParameter(SoundPlayerData.OutputVolumeName, SoundPlayerData.OutputVolume);
}


void AAudioCuePlayer::PlayAndDestroy()
{
	const FOnQuartzCommandEventBP EmptyDelegate;

	// AudioComponent->Play();
	AudioComponent->PlayQuantized(GetWorld(), Clock, QuartzQuantizationBoundary, EmptyDelegate);

	AudioComponent->OnAudioFinished.AddDynamic(this, &AAudioCuePlayer::DestroyActor);
}


void AAudioCuePlayer::DestroyActor()
{
	Destroy();
}
