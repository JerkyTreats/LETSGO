// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumData.h"


FDrumPattern::FDrumPattern()
{
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
			FPerBarSchedule({1.0f, 3.0f}),
			FPerBarSchedule({1.0f, 3.0f}),
			FPerBarSchedule({1.0f, 3.0f}),
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f}),
		}
	);
	BasicRock.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f, 4.0f}),
		}
	);
	
	BasicRock.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
	BasicRock.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	BasicRock.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Four on the Floor
	FourOnTheFloor.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f}),
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f}),
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f}),
			FPerBarSchedule({}),
		}
	);
	FourOnTheFloor.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f, 4.0f}),
		}
	);
	
	FourOnTheFloor.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
	FourOnTheFloor.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	FourOnTheFloor.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Funk
	Funk.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 5.0f}),
			FPerBarSchedule({1.0f, 5.0f}),
			FPerBarSchedule({1.0f, 5.0f}),
			FPerBarSchedule({1.0f, 3.0f, 5.0f, 7.0f}),
		}
	);
	
	Funk.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f, 4.0f}),
		}
	);
	
	Funk.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
	Funk.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Funk.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);


	// Bossa Nova
	BossaNova.Kick =FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 4.0f, 5.0f, 8.0f}),
			FPerBarSchedule({1.0f, 4.0f, 5.0f, 8.0f}),
		}
	);
	BossaNova.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 4.0f, 7.0f}),
			FPerBarSchedule({3.0f, 5.0f}),
		}
	);
	
	BossaNova.HiHatOpen =FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
		
	BossaNova.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	BossaNova.Clap =  FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Samba
	Samba.Kick = FInstrumentSchedule(
	EQuartzCommandQuantization::EighthNote, 
	{
		FPerBarSchedule({1.0f, 4.0f, 5.0f, 8.0f}),
		FPerBarSchedule({1.0f, 4.0f, 5.0f, 8.0f}),
		}
	);
	
	Samba.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule({1.0f, 4.0f, 7.0f, 10.0f}),
		}
	);
	
	Samba.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
		
	Samba.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}),
		}
	);
	
	Samba.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Shuffle
	Shuffle.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({1.0f, 3.0f}),
		}
	);
	
	Shuffle.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f, 4.0f}),
		}
	);
	
	Shuffle.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
		
	Shuffle.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule({1.0f, 3.0f, 4.0f, 6.0f, 7.0f, 9.0f, 10.0, 12.0}),
		}
	);
	
	Shuffle.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// HalfTimeShuffle
	HalfTimeShuffle.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({1.0f, 3.0f}),
		}
	);
	
	HalfTimeShuffle.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule({2.0f, 5.0f, 7.0f, 8.0f, 11.0f}),
		}
	);
	
	HalfTimeShuffle.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
		
	HalfTimeShuffle.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule({1.0f, 3.0f, 4.0f, 6.0f, 7.0f, 9.0f, 10.0, 12.0}),
		}
	);
	
	HalfTimeShuffle.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// DiscoGroove
	DiscoGroove.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f}),
		}
	);
	
	DiscoGroove.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f, 4.0f}),
		}
	);
	
	DiscoGroove.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote,
		{
			FPerBarSchedule({2.0f, 4.0f, 6.0f, 8.0f}),
		}
	);
		
	DiscoGroove.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 3.0f, 5.0f, 7.0f }),
		}
	);
	
	DiscoGroove.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Motown
	Motown.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 3.0f, 5.0f, 6.0f, 8.0}),
		}
	);
	Motown.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 3.0f, 5.0f, 7.0}),
		}
	);
	
	Motown.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
	Motown.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Motown.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Swing
	Swing.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{}
	);
	Swing.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule({3.0f, 7.0f}),
		}
	);
	
	Swing.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNoteTriplet, 
		{
			FPerBarSchedule({1.0f, 4.0f, 6.0f, 7.0f, 10.0f, 12.0f}),
		}
	);
	
	Swing.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f, 4.0f}),
		}
	);
	
	Swing.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Reggae
	Reggae.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({3.0f, 7.0f}),
		}
	);
	
	Reggae.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({3.0f, 7.0f}),
		}
	);
	
	Reggae.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
	Reggae.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Reggae.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Pop
	Pop.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 6.0f}),
		}
	);
	
	Pop.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({3.0f, 7.0f}),
		}
	);
	
	Pop.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
	Pop.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}),
		}
	);
	
	Pop.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// Country
	Country.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f}),
		}
	);
	
	Country.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule({3.0f, 7.0f, 11.0f, 12.0f, 14.0f, 15.0f}),
		}
	);
	
	Country.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({2.0f, 4.0f, 6.0f, 8.0f}),
		}
	);
	
	Country.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 4.0f, 5.0f, 6.0f, 8.0f, 9.0f, 10.0f, 13.0, 16.0}),
		}
	);
	
	Country.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);

	// SixteenthNoteGroove
	SixteenthGroove.Kick = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({1.0f, 5.0f, 6.0f}),
		}
	);
	
	SixteenthGroove.Snare = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{
			FPerBarSchedule({2.0f,4.0f}),
		}
	);
	
	SixteenthGroove.HiHatOpen = FInstrumentSchedule(
		EQuartzCommandQuantization::EighthNote, 
		{
			FPerBarSchedule({2.0f, 4.0f, 6.0f, 8.0f}),
		}
	);
	
	SixteenthGroove.HiHatClosed = FInstrumentSchedule(
		EQuartzCommandQuantization::SixteenthNote, 
		{
			FPerBarSchedule({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0, 14.0f, 15.0f, 16.0}),
		}
	);
	
	SixteenthGroove.Clap = FInstrumentSchedule(
		EQuartzCommandQuantization::QuarterNote, 
		{}
	);
	
}

DrumData::~DrumData()
{
}
