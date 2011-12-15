#pragma once
#include <BWAPI.h>
#include "hugin"
#include "InformationEnums.h"
#include "StrategyManager.h"
#include "BayesianNetwork.h"

class BuildOrderPredictor
{
public:
	BuildOrderPredictor();
	void InitializePredictionNetwork(InformationEnums::Matchup matchup);
	void UpdatePredictionNetwork(BWAPI::UnitType building);
	void UpdatePredictionNetwork(BWAPI::UpgradeType upgrade);
	InformationEnums::ThreatLevel GetCurrentThreatLevel();
private:
	bool protossOpeningDone;
	InformationEnums::Matchup matchup;
	BayesianNetwork predictionNetwork;
	std::map<BWAPI::UnitType,int> enemyBuildingsOwned;
	void UpdateTvTNetwork(BWAPI::UnitType building);
	void UpdateTvPNetwork(BWAPI::UnitType building);
	void UpdateTvZNetwork(BWAPI::UnitType building);
};
