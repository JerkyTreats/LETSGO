// Fill out your copyright notice in the Description page of Project Settings.


#include "StartDrums.h"
#include "Drum/DrumData.h"
#include "Drum/DrumSoundCueMapping.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AStartDrums::AStartDrums()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<AInstrument>(TEXT("Drums"));
}

// Called when the game starts or when spawned
void AStartDrums::BeginPlay()
{
	Super::BeginPlay();

}

EDrumPatterns AStartDrums::GetRandomDrumPattern()
{
	TArray Patterns = {
		BasicRock,
		FourOnTheFloor,
		Funk,
		BossaNova,
		Samba,
		Shuffle,
		HalfTimeShuffle,
		DiscoGroove,
		Motown,
		Swing,
		Reggae,
		Pop,
		Country,
		SixteenthNoteGroove
	};

	const int Rand = FMath::RandRange(0, Patterns.Num()-1);
	return Patterns[Rand];
}

FDrumPattern AStartDrums::GetDrumData(const EDrumPatterns Pattern)
{
	DrumData Data = DrumData();
	
	switch (Pattern)
	{
	case BasicRock:
		return Data.BasicRock;
	case FourOnTheFloor:
		return Data.FourOnTheFloor;
	case Funk:
		return Data.Funk;
	case BossaNova:
		return Data.BossaNova;
	case Samba:
		return Data.Samba;
	case Shuffle:
		return Data.Shuffle;
	case HalfTimeShuffle:
		return Data.HalfTimeShuffle;
	case DiscoGroove:
		return Data.DiscoGroove;
	case Motown:
		return Data.Motown;
	case Swing:
		return Data.Swing;
	case Reggae:
		return Data.Reggae;
	case Pop:
		return Data.Pop;
	case Country:
		return Data.Country;
	case SixteenthNoteGroove:
		return Data.SixteenthGroove;
		
	default:
		return Data.BasicRock;
	}
}

// Called every frame
void AStartDrums::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AStartDrums::Initialize()
{
	const EDrumPatterns DrumPattern = GetRandomDrumPattern();
	const FDrumPattern Pattern = GetDrumData(DrumPattern);

	const ADrumSoundCueMapping* SoundCueMapping = GetWorld()->SpawnActor<ADrumSoundCueMapping>(ADrumSoundCueMappingClass);

	// Initialize Kick
	Kick = GetWorld()->SpawnActorDeferred<AInstrument>(AInstrument::StaticClass(), FTransform());
	Kick->Initialize(Pattern.Kick, SoundCueMapping->Kick);
	Kick->FinishSpawning(FTransform());

	//Initialize Snare
	Snare = GetWorld()->SpawnActorDeferred<AInstrument>(AInstrument::StaticClass(), FTransform());
	Snare->Initialize(Pattern.Snare, SoundCueMapping->Snare);
	Snare->FinishSpawning(FTransform());

	//Initialize HiHatOpen
	HiHatOpen = GetWorld()->SpawnActorDeferred<AInstrument>(AInstrument::StaticClass(), FTransform());
	HiHatOpen->Initialize(Pattern.HiHatOpen, SoundCueMapping->HiHatOpen);
	HiHatOpen->FinishSpawning(FTransform());

	//Initialize HiHatOpen
	HiHatClosed = GetWorld()->SpawnActorDeferred<AInstrument>(AInstrument::StaticClass(), FTransform());
	HiHatClosed->Initialize(Pattern.HiHatClosed, SoundCueMapping->HiHatClosed);
	HiHatClosed->FinishSpawning(FTransform());

	//Initialize Clap
	Clap = GetWorld()->SpawnActorDeferred<AInstrument>(AInstrument::StaticClass(), FTransform());
	Clap->Initialize(Pattern.Clap, SoundCueMapping->Clap);
	Clap->FinishSpawning(FTransform());
	
	// ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(GetWorld()->GetAuthGameMode());
	// InstrumentRack = GameMode->GetInstrumentRack();
	// InstrumentRack->AddInstrument(Drums);
}


void AStartDrums::Activate()
{
	UE_LOG(LogTemp, Display, TEXT("Phase StartDrums Activated"))
	Kick->StartPlaying();
	Snare->StartPlaying();
	HiHatOpen->StartPlaying();
	HiHatClosed->StartPlaying();
	Clap->StartPlaying();
	IsComplete = true;

}

bool AStartDrums::IsActivated()
{
	return IsActive;
}

void AStartDrums::Deactivate()
{
}

void AStartDrums::Complete()
{
	UE_LOG(LogTemp, Display, TEXT("Phase StartDrums Completed"))
	InitiateDestroy();
}

bool AStartDrums::IsCompleted()
{
	return IsComplete;
}

void AStartDrums::InitiateDestroy()
{
	Destroy();
}

