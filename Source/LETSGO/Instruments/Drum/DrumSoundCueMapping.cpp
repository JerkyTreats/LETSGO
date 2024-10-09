// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumSoundCueMapping.h"


// Sets default values
ADrumSoundCueMapping::ADrumSoundCueMapping(): Kick(nullptr), Snare(nullptr), HiHatOpen(nullptr), HiHatClosed(nullptr),
                                              Clap(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADrumSoundCueMapping::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrumSoundCueMapping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FInstrumentData ADrumSoundCueMapping::GenerateInstrumentData(USoundWave* Sound)
{
	const FMetaSoundPlayerData MetaSound = FMetaSoundPlayerData(Sound);
	const TArray<FInstrumentNote> Notes {
		FInstrumentNote(0, C, MetaSound)
	};
	return FInstrumentData(Notes);
}

FInstrumentData ADrumSoundCueMapping::GetInstrumentData(const EInstrumentRoles InstrumentRole) const
{
	switch (InstrumentRole)
	{
	case EInstrumentRoles::Snare:
		{
			return GenerateInstrumentData(Snare);
		}
	case EInstrumentRoles::Kick:
		{
			return GenerateInstrumentData(Kick);
		}
	case EInstrumentRoles::HiHatClosed:
		{
			return GenerateInstrumentData(HiHatClosed);
		}
	case EInstrumentRoles::HiHatOpen:
		{
			return GenerateInstrumentData(HiHatOpen);
		}
	case EInstrumentRoles::Clap:
		{
			return GenerateInstrumentData(Clap);
		}	
	default:
		{
			UE_LOG(LogLetsgo, Warning, TEXT("Default case returned for GetInstrumentData"))
			return FInstrumentData();
		}
	}
}

