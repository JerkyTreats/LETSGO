// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumsAudioCuePlayer.h"
#include "Components/AudioComponent.h"


// Sets default values
ADrumsAudioCuePlayer::ADrumsAudioCuePlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Attached Audio Component"));
	SetRootComponent(AudioComponent);
	AudioComponent->SetAutoActivate(false); // Don't play immediately
	AudioComponent->bAllowSpatialization = false; // Don't play in world
}

// Called when the game starts or when spawned
void ADrumsAudioCuePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrumsAudioCuePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADrumsAudioCuePlayer::Initialize(UMetaSoundSource* ParentMetaSoundSource, UQuartzClockHandle* ParentClock,
	FQuartzQuantizationBoundary ParentQuartzQuantizationBoundary)
{
	Clock = ParentClock;
	MetaSoundSource = ParentMetaSoundSource;
	QuartzQuantizationBoundary = ParentQuartzQuantizationBoundary;

	AudioComponent->SetSound(MetaSoundSource);
}

void ADrumsAudioCuePlayer::Play()
{
	const FOnQuartzCommandEventBP EmptyDelegate;
	IsSoundPlaying = true;
	AudioComponent->PlayQuantized(GetWorld(), Clock, QuartzQuantizationBoundary, EmptyDelegate);
	AudioComponent->OnAudioFinished.AddDynamic(this, &ADrumsAudioCuePlayer::ResetAudioCue);
}

void ADrumsAudioCuePlayer::PlayAndDestroy()
{
	const FOnQuartzCommandEventBP EmptyDelegate;
	AudioComponent->PlayQuantized(GetWorld(), Clock, QuartzQuantizationBoundary, EmptyDelegate);
	AudioComponent->OnAudioFinished.AddDynamic(this, &ADrumsAudioCuePlayer::DestroyActor);
}

void ADrumsAudioCuePlayer::ResetAudioCue()
{
	IsSoundPlaying = false;
}


void ADrumsAudioCuePlayer::DestroyActor()
{
	Destroy();
}
