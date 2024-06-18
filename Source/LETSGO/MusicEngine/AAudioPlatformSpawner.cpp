// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioPlatformSpawner.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AAudioPlatformSpawner::AAudioPlatformSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NoteContainer = CreateDefaultSubobject<UNoteContainer>(TEXT("Note Container"));
	
}

// Called when the game starts or when spawned
void AAudioPlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAudioPlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FTransform AAudioPlatformSpawner::GetCameraVectorForward() const
{
	// Assumes only a single local player in the world at index 0
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);

	const APawn* PlayerControlledPawn = PlayerController->GetPawn();
	const FVector PawnVector = PlayerControlledPawn->GetActorLocation();
	

	const FVector CameraForward = CameraManager->GetActorForwardVector();

	// Get the camera location and offset by some amount
	// Added to the player controlled pawn location
	// Gives you a world location where the player is looking
	const FVector Vector = FVector(
		(CameraForward.X * CameraVectorForwardOffsetAmount.X) + PawnVector.X,
		(CameraForward.Y * CameraVectorForwardOffsetAmount.Y) + PawnVector.Y,
		0
		);
	
	const FTransform VectorTransform = FTransform(Vector);
	return VectorTransform;
}

AAudioPlatform* AAudioPlatformSpawner::SpawnPlatform(const FTransform& SpawnLocation, FLetsGoMusicNotes Note)
{
	FVector Location = SpawnLocation.GetTranslation();
	FRotator Rotation = SpawnLocation.Rotator();
	FActorSpawnParameters SpawnInfo;
	
	AAudioPlatform* SpawnedPlatform = GetWorld()->SpawnActor<AAudioPlatform>(Location, Rotation, SpawnInfo);

	SpawnedPlatform->Note = Note;
	return SpawnedPlatform;
}

