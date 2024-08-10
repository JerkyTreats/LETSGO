// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InstrumentSchedule.generated.h"


USTRUCT()
struct FPerBarSchedule
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<float> BeatsInBar; // [1, 3] plays sound on first and third beat

	FPerBarSchedule() {}
	explicit FPerBarSchedule(const TArray<float>& Beats) : BeatsInBar(Beats) {}
};

USTRUCT()
struct FInstrumentSchedule
{
	GENERATED_BODY()

	UPROPERTY()
	EQuartzCommandQuantization QuantizationDivision;
	
	UPROPERTY()
	TArray<FPerBarSchedule> BeatSchedule; // [[1,3],[1,3],[1,3],[1,2,3,4]] play 1-3, on 4th bar 4onfloor

	FInstrumentSchedule(): QuantizationDivision() {} ;
	explicit FInstrumentSchedule(const EQuartzCommandQuantization Quantization): QuantizationDivision(Quantization) {}
};
