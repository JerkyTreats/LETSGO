// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumData.h"


FDrumPattern::FDrumPattern()
{
}

DrumData::DrumData(UMetaSoundSource* Kick, UMetaSoundSource* Snare, UMetaSoundSource* HiHatClosed,
	UMetaSoundSource* HiHatOpen, UMetaSoundSource* Clap)
{
	KickSound = Kick;
	SnareSound = Snare;
	HiHatClosedSound = HiHatClosed;
	HiHatOpenSound = HiHatOpen;
	ClapSound = Clap;
}

DrumData::DrumData()
{
	BasicRock = FDrumPattern();
	FourOnTheFloor = FDrumPattern();
	Funk = FDrumPattern();
	BossaNova = FDrumPattern();
	Motown = FDrumPattern();
	Reggae = FDrumPattern();
	Pop = FDrumPattern();
	SixteenthGroove = FDrumPattern();


	
	// Basic Rock	
	BasicRock.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(KickSound, {1.0f, 3.0f}),
		}
	);
	BasicRock.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(SnareSound, {2.0f, 4.0f}),
		}
	);
	
	BasicRock.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{FPerBarSchedule({})}
	);
	
	BasicRock.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound, {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	BasicRock.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{FPerBarSchedule({})}
	);

	// Four on the Floor
	FourOnTheFloor.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 2.0f, 3.0f, 4.0f}),
		}
	);
	FourOnTheFloor.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(SnareSound,{2.0f, 4.0f}),
		}
	);
	
	FourOnTheFloor.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{FPerBarSchedule({})}
	);
	
	FourOnTheFloor.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	FourOnTheFloor.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote,
		{FPerBarSchedule({})}
	);

	// Funk
	Funk.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 5.0f}),
		}
	);
	
	Funk.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(SnareSound,{2.0f, 4.0f}),
		}
	);
	
	Funk.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
	
	Funk.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Funk.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);


	// Bossa Nova
	BossaNova.Kick =FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 4.0f, 5.0f, 8.0f}),
		}
	);
	BossaNova.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(SnareSound,{1.0f, 4.0f, 7.0f}),
			FPerBarSchedule(SnareSound,{3.0f, 5.0f}),
		}
	);
	
	BossaNova.HiHatOpen =FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
		
	BossaNova.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	BossaNova.Clap =  FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Samba
	Samba.Kick = FInstrumentSchedule(
	EQuartzCommandQuantization::EighthNote, 
	{
		FPerBarSchedule(KickSound,{1.0f, 4.0f, 5.0f, 8.0f}),
		}
	);
	
	Samba.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule(SnareSound,{1.0f, 4.0f, 7.0f, 10.0f}),
		}
	);
	
	Samba.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
		
	Samba.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}),
		}
	);
	
	Samba.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Shuffle
	Shuffle.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 3.0f}),
		}
	);
	
	Shuffle.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(SnareSound,{2.0f, 4.0f}),
		}
	);
	
	Shuffle.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
		
	Shuffle.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 3.0f, 4.0f, 6.0f, 7.0f, 9.0f, 10.0, 12.0}),
		}
	);
	
	Shuffle.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// HalfTimeShuffle
	HalfTimeShuffle.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 3.0f}),
		}
	);
	
	HalfTimeShuffle.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule(SnareSound,{2.0f, 5.0f, 7.0f, 8.0f, 11.0f}),
		}
	);
	
	HalfTimeShuffle.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
		
	HalfTimeShuffle.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 3.0f, 4.0f, 6.0f, 7.0f, 9.0f, 10.0, 12.0}),
		}
	);
	
	HalfTimeShuffle.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// DiscoGroove
	DiscoGroove.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 2.0f, 3.0f, 4.0f}),
		}
	);
	
	DiscoGroove.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(SnareSound,{2.0f, 4.0f}),
		}
	);
	
	DiscoGroove.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote,
		{
			FPerBarSchedule(HiHatOpenSound,{2.0f, 4.0f, 6.0f, 8.0f}),
		}
	);
		
	DiscoGroove.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 3.0f, 5.0f, 7.0f }),
		}
	);
	
	DiscoGroove.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Motown
	Motown.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 3.0f, 5.0f, 6.0f, 8.0}),
		}
	);
	Motown.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(SnareSound,{1.0f, 3.0f, 5.0f, 7.0}),
		}
	);
	
	Motown.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
	
	Motown.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Motown.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Swing
	Swing.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
{FPerBarSchedule({})}
	);
	Swing.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule(SnareSound,{3.0f, 7.0f}),
		}
	);
	
	Swing.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule(HiHatOpenSound,{1.0f, 4.0f, 6.0f, 7.0f, 10.0f, 12.0f}),
		}
	);
	
	Swing.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(HiHatClosedSound, {2.0f, 4.0f}),
		}
	);
	
	Swing.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Reggae
	Reggae.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(KickSound,{3.0f, 7.0f}),
		}
	);
	
	Reggae.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(SnareSound,{3.0f, 7.0f}),
		}
	);
	
	Reggae.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
	
	Reggae.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Reggae.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Pop
	Pop.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 6.0f}),
		}
	);
	
	Pop.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(SnareSound,{3.0f, 7.0f}),
		}
	);
	
	Pop.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
	
	Pop.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Pop.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// Country
	Country.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 2.0f, 3.0f, 4.0f}),
		}
	);
	
	Country.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule(SnareSound,{3.0f, 7.0f, 11.0f, 12.0f, 14.0f, 15.0f}),
		}
	);
	
	Country.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatOpenSound,{2.0f, 4.0f, 6.0f, 8.0f}),
		}
	);
	
	Country.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 4.0f, 5.0f, 6.0f, 8.0f, 9.0f, 10.0f, 13.0, 16.0}),
		}
	);
	
	Country.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);

	// SixteenthNoteGroove
	SixteenthGroove.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(KickSound,{1.0f, 5.0f, 6.0f}),
		}
	);
	
	SixteenthGroove.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule(SnareSound,{2.0f,4.0f}),
		}
	);
	
	SixteenthGroove.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule(HiHatOpenSound,{2.0f, 4.0f, 6.0f, 8.0f}),
		}
	);
	
	SixteenthGroove.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule(HiHatClosedSound,{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0, 14.0f, 15.0f, 16.0}),
		}
	);
	
	SixteenthGroove.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
{FPerBarSchedule({})}
	);
	
}

DrumData::~DrumData()
{
}
