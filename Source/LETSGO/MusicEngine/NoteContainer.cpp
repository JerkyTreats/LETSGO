// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteContainer.h"

UNoteContainer::UNoteContainer()
{
}

UNoteContainer::UNoteContainer(const TArray<FLetsGoMusicNotes>& Notes)
{
	this -> Notes = Notes;
}

FLetsGoMusicNotes UNoteContainer::PopNextNote()
{
	const FLetsGoMusicNotes Note = Notes[0];
	Notes.RemoveAt(0);
	return Note;	
}

void UNoteContainer::AddNotes(const TArray<FLetsGoMusicNotes>& NotesToAdd)
{
	Notes.Append(NotesToAdd);
}
