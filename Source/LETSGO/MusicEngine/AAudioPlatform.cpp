// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioPlatform.h"
#include "GameFramework/Character.h"

AAudioPlatform::AAudioPlatform()
{
	AudioCuePlayer = CreateDefaultSubobject<UAudioCuePlayer>(TEXT("Audio Cue Player"));
	ParticleController = CreateDefaultSubobject<UParticleController>(TEXT("Particle Controller"));
}

void AAudioPlatform::BeginPlay()
{

	// FTransform EmptyTransform;
	// AudioCuePlayer = AddComponentByClass(AudioCuePlayer, true, EmptyTransform, false);

	// AudioCuePlayer = AddInstance
	// AudioCuePlayer->RegisterComponent();
	//this->AddInstanceComponent(AudioCuePlayer);

	AudioCuePlayer->ReadyForCleanUp.AddDynamic(this, &AAudioPlatform::OnAudioCuePlatformReadyForCleanup);
	

	ParticleController->OnReadyForCleanUp.AddDynamic(this, &AAudioPlatform::OnParticleControllerReadyForCleanup);
	// AudioCuePlayer->RegisterComponent();
	// this->AddInstanceComponent(AudioCuePlayer);
	
	Super::BeginPlay(); 
}


void AAudioPlatform::InitializeAudioPlatform(FLetsGoMusicNotes MusicNote, UStaticMeshComponent* Mesh, const FQuartzQuantizationBoundary& QuartzQuantizationBoundary)
{
	Note = MusicNote;
	MeshComponent = Mesh;
	
	AudioCuePlayer->QuartzQuantizationBoundary = QuartzQuantizationBoundary;
	AudioCuePlayer->AudioPlatformReference = this;

	ParticleController->Note = Note;
	ParticleController->Mesh = MeshComponent;

	OnAudioPlatformInitialized.Broadcast();
}

void AAudioPlatform::OnAudioCuePlatformReadyForCleanup()
{
	AudioCuePlayer->DestroyComponent();
	AudioCuePlayer_Destroyed = true;
	PostDestroy();
}

void AAudioPlatform::OnParticleControllerReadyForCleanup()
{
	ParticleController->DestroyComponent();
	ParticleController_Destroyed = true;
	PostDestroy();
}


void AAudioPlatform::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	// Only broadcast if it's a player character
	if (Cast<ACharacter>(OtherActor))
	{
		OnAudioPlatformTriggered.Broadcast(Note);
		
		FTimerHandle MemberTimerHandle;
		// Allow slight delay then destroy this platform
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AAudioPlatform::PreDestroy, ActorDestroyDelay, false);
	}
}

void AAudioPlatform::PreDestroy()
{
	MeshComponent->DestroyComponent();
	AudioPlatform_ReadyForCleanup = true;
}

void AAudioPlatform::PostDestroy()
{
	if (AudioPlatform_ReadyForCleanup && AudioCuePlayer_Destroyed && ParticleController_Destroyed )
	{
		Destroy();
	}
}



