#include "StrategyManager.h"
#include "BuildOrderPredictor.h"

BuildOrderPredictor *buildOrderPredictor;
bool StrategyManager::initialized= false;
StrategyManager* StrategyManager::strategyManager = 0;
StrategyManager* StrategyManager::GetInstance()
{
	if(strategyManager == 0)
	{
		strategyManager = new StrategyManager();
	}
	return strategyManager;
}
StrategyManager::StrategyManager()
{
}

void StrategyManager::Update()
{
	if(StrategyManager::initialized)
	{
		
	}
	else
	{
		if(BWAPI::Broodwar->enemy()->getRace() == BWAPI::Races::Zerg){matchup = InformationEnums::MatchupTvZ;}
		else if(BWAPI::Broodwar->enemy()->getRace() == BWAPI::Races::Protoss){matchup = InformationEnums::MatchupTvP;}
		else if(BWAPI::Broodwar->enemy()->getRace() == BWAPI::Races::Terran){matchup = InformationEnums::MatchupTvT;}
		buildOrderPredictor = new BuildOrderPredictor();
		buildOrderPredictor->InitializePredictionNetwork(matchup);
		StrategyManager::initialized = true;
	}
}
