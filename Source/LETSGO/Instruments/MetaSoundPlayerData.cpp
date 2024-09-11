// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaSoundPlayerData.h"


FMetaSoundPlayerData::FMetaSoundPlayerData(): WaveAsset(nullptr)
{
}

FMetaSoundPlayerData::FMetaSoundPlayerData(USoundWave* Cue)
{
	WaveAsset = Cue;
}

FMetaSoundPlayerData::FMetaSoundPlayerData(USoundWave* Cue, const float Volume)
{
	WaveAsset = Cue;
	OutputVolume = Volume;
}

FMetaSoundPlayerData::~FMetaSoundPlayerData()
{
}
