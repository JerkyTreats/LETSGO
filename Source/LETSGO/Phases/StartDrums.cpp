// Fill out your copyright notice in the Description page of Project Settings.


#include "StartDrums.h"
#include "LETSGO/Instruments/Drum/DrumData.h"
#include "LETSGO/Instruments/Drum/DrumSoundCueMapping.h"
#include "LETSGO/LETSGO.h"
#include "LETSGO/GameModes/ALetsGoGameMode.h"


// Sets default values
AStartDrums::AStartDrums()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<AInstrument>(TEXT("Drums"));

	PlayQuantizationDelegate.BindUFunction(this, "OnQuantizationBoundaryTriggered");
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
	const ADrumSoundCueMapping* SoundCueMapping = GetWorld()->SpawnActor<ADrumSoundCueMapping>(ADrumSoundCueMappingClass);
	DrumData Data = DrumData(SoundCueMapping->Kick,SoundCueMapping->Snare,SoundCueMapping->HiHatClosed,SoundCueMapping->HiHatOpen,SoundCueMapping->Clap);
	
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

	if(GEngine)
	{
		TEnumAsByte<EDrumPatterns> PatEnum = DrumPattern;
		FString EnumAsString = UEnum::GetValueAsString(PatEnum.GetValue());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, EnumAsString);	
	}

	// Initialize Kick
	Kick = GetWorld()->SpawnActorDeferred<AInstrument>(InstrumentClass, FTransform());
	Kick->InitializeSingleSchedule(Pattern.Kick);
	Kick->FinishSpawning(FTransform());
	
	//Initialize Snare
	Snare = GetWorld()->SpawnActorDeferred<AInstrument>(InstrumentClass, FTransform());
	Snare->InitializeSingleSchedule(Pattern.Snare);
	Snare->FinishSpawning(FTransform());	

	//Initialize HiHatOpen
	HiHatOpen = GetWorld()->SpawnActorDeferred<AInstrument>(InstrumentClass, FTransform());
	HiHatOpen->InitializeSingleSchedule(Pattern.HiHatOpen);
	HiHatOpen->FinishSpawning(FTransform());

	//Initialize HiHatOpen
	HiHatClosed = GetWorld()->SpawnActorDeferred<AInstrument>(InstrumentClass, FTransform());
	HiHatClosed->InitializeSingleSchedule(Pattern.HiHatClosed);
	HiHatClosed->FinishSpawning(FTransform());

	//Initialize Clap
	Clap = GetWorld()->SpawnActorDeferred<AInstrument>(InstrumentClass, FTransform());
	Clap->InitializeSingleSchedule(Pattern.Clap);
	Clap->FinishSpawning(FTransform());

	Kick->Initialize(true);
	Snare->Initialize(true);
	HiHatOpen->Initialize(true);
	HiHatClosed->Initialize(true);
	Clap->Initialize(true);
}


void AStartDrums::Activate()
{
	UE_LOG(LogLetsgo, Display, TEXT("Phase StartDrums Activated"))

	// Start the drums on the next Bar. This should ensure that all clocks are in sync
	const UWorld* World = GetWorld();
	const ALetsGoGameMode* GameMode = Cast<ALetsGoGameMode>(World->GetAuthGameMode());
	const AClockSettings* ClockSettings = GameMode->GetClockSettings();
	UQuartzClockHandle* MainClock = ClockSettings->MainClock;

	MainClock->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Bar, PlayQuantizationDelegate, MainClock);
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
	UE_LOG(LogLetsgo, Display, TEXT("Phase StartDrums Completed"))
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

void AStartDrums::OnQuantizationBoundaryTriggered(FName ClockName, EQuartzCommandQuantization QuantizationType,
	int32 NumBars, int32 Beat, float BeatFraction)
{

	IsComplete = true;
}

