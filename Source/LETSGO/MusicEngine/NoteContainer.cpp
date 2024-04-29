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
	return Notes.Pop();	
}

void UNoteContainer::AddNotes(const TArray<FLetsGoMusicNotes>& NotesToAdd)
{
	Notes.Append(NotesToAdd);
}
