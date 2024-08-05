// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioCuePlayerPool.h"
#include "DrumsAudioCuePlayer.h"
#include "MetasoundSource.h"
#include "Quartz/AudioMixerClockHandle.h"

void UAudioCuePlayerPool::InitializeCuePool(UMetaSoundSource* MetaSoundSource, UQuartzClockHandle* Clock, const FQuartzQuantizationBoundary& QuartzQuantizationBoundary) const
{
	for (int i = 0; i < CuePoolSize; i++)
	{
		
		
	}
}
/*
void UAudioCuePlayerPool::Initialize(FActorSpawnParameters CuePlayerCloneParameters, UWorld* World)
{
	for (int i = 0; i < CuePoolSize; i++)
	{
		ADrumsAudioCuePlayer* Clone = World->SpawnActor<ADrumsAudioCuePlayer>(CuePlayerCloneParameters);
		AudioCuePool.Emplace(Clone);
	}
}
*/
void UAudioCuePlayerPool::PlayFreeAudioCue()
{
	for (int i = 0; i < CuePoolSize; i++)
	{
		if ( ! AudioCuePool[i]->IsSoundPlaying)
		{
			AudioCuePool[i]->Play();
		}
	}
}
