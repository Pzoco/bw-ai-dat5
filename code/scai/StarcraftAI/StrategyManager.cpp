#include "StrategyManager.h"


StrategyManager* StrategyManager::strategyManager = 0;
StrategyManager* StrategyManager::GetInstance()
{
	if(strategyManager == 0)
	{
		strategyManager = new StrategyManager();
	}
	return strategyManager;
}
StrategyManager::StrategyManager(void)
{
}

void StrategyManager::Update()
{
	if(initialized)
	{
	}
	else
	{
		InitializePredictionNetwork();
		currentThreatLevel = InformationEnums::ThreatLow;
	}
}
void StrategyManager::InitializePredictionNetwork()
{
	networksFilePath = ExePath();
	DefaultParseListener pl;
	if(BWAPI::Broodwar->enemy()->getRace() == BWAPI::Races::Zerg)
	{
		StrategyManager::matchup = InformationEnums::MatchupTvZ;
		this->predictionNetwork = Domain(networksFilePath+"tvtprediction.net",&pl);
	}
	else if(BWAPI::Broodwar->enemy()->getRace() == BWAPI::Races::Protoss)
	{
		StrategyManager::matchup = InformationEnums::MatchupTvP;
		this->predictionNetwork = Domain(networksFilePath+"tvtprediction.net",&pl);
	}
	else if(BWAPI::Broodwar->enemy()->getRace() == BWAPI::Races::Terran)
	{
		StrategyManager::matchup = InformationEnums::MatchupTvT;
		this->predictionNetwork = Domain(networksFilePath+"tvtprediction.net",&pl);
	}
}