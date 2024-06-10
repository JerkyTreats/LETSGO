// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULetsGoMusicEngine.h"
#include "UObject/Object.h"
#include "UNoteContainer.generated.h"

/**
 * A container of Notes 
 */
UCLASS(BlueprintType)
class LETSGO_API UNoteContainer : public UObject
{
	GENERATED_BODY()

	
public:
	UNoteContainer() {};

	explicit UNoteContainer(const TArray<FLetsGoMusicNotes>& Notes)
	{
		this -> Notes = Notes;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLetsGoMusicNotes> Notes;

	UFUNCTION(BlueprintCallable, Category="LetsGo | AudioPlatform")
	bool PopNextNote(FLetsGoMusicNotes& PoppedNote);

	UFUNCTION(BlueprintCallable, Category="LetsGo | AudioPlatform")
	void AddNotes(const TArray<FLetsGoMusicNotes>& NotesToAdd);
	
};
