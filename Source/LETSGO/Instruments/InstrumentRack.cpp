// Fill out your copyright notice in the Description page of Project Settings.


#include "InstrumentRack.h"

UInstrumentRack::UInstrumentRack()
{
}

void UInstrumentRack::AddInstrument(AActor* Instrument)
{
	Instruments.Emplace(Instrument);
}
