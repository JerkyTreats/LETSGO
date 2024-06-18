// Fill out your copyright notice in the Description page of Project Settings.


#include "UNoteContainer.h"

bool UNoteContainer::PopNextNote(FLetsGoMusicNotes& PoppedNote)
{
	if (Notes.Num() > 0)
	{
		PoppedNote = Notes[0];
		Notes.RemoveAt(0);
		return true;	
	}
	return false;
}

void UNoteContainer::AddNotes(const TArray<FLetsGoMusicNotes>& NotesToAdd)
{
	Notes.Append(NotesToAdd);
}

int UNoteContainer::GetNumberOfNotes() const
{
	return Notes.Num();
}
