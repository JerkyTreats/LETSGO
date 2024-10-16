#include "ComposerData.h"


FComposerData::FComposerData(const EInstrumentRoles InRole, const FInstrumentData& InData)
{
	FComposerData();
	InstrumentRole = InRole;
	InstrumentData = InData;

}

bool FComposerData::IsMultiNoteInstrument() const
{
	switch (InstrumentRole)
	{
	case Kick:
		return false;
	case HiHatClosed:
		return false;
	case HiHatOpen:
		return false;
	case Snare:
		return false;
	case Clap:
		return false;
	default:
		return true;
	}
}

/*
FInstrumentInputData::FInstrumentInputData(const FComposerData& InputData)
{
	ComposerData = InputData;
}

FMusicStrategyData::FMusicStrategyData(): Strategy(nullptr)
{
	InstrumentInputs = TArray<FInstrumentInputData>();
}
*/

/*FMusicStrategyData::FMusicStrategyData()
{
}

FMusicStrategyData::FMusicStrategyData(IMusicStrategy* InputStrategy, const float Appropriateness, const EMusicStrategies InStrategyType)
{
	FMusicStrategyData();
	Strategy = InputStrategy;
	StrategyAppropriateness = Appropriateness;
	StrategyType = InStrategyType;
}*/

/*
void FMusicStrategyData::GenerateInstrumentInputs(const TArray<FComposerData> ComposerDataSet)
{
	// Clear the Array
	InstrumentInputs.Empty();

	// Rebuild the Array
	for(int i = 0; i < ComposerDataSet.Num(); i++)
	{
		FInstrumentInputData Data = FInstrumentInputData(ComposerDataSet[i]);
		
		// Get instrument appropriateness
		Data.Appropriateness = Strategy->GetInstrumentAppropriateness(ComposerDataSet[i], ComposerDataSet);
		
		InstrumentInputs.Emplace(Data);
	}
}
*/

