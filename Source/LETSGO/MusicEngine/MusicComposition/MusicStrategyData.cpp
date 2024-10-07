#include "MusicStrategyData.h"

FMusicStrategyData::FMusicStrategyData(): Strategy(nullptr)
{
	InstrumentInputs = TArray<FInstrumentInputData>();
}

FMusicStrategyData::FMusicStrategyData(IMusicStrategy* InputStrategy, const float Appropriateness)
{
	FMusicStrategyData();
	Strategy = InputStrategy;
	StrategyAppropriateness = Appropriateness;
}

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

	// Generate Appropriateness
	Strategy->GetStrategyAppropriateness(ComposerDataSet);
}

