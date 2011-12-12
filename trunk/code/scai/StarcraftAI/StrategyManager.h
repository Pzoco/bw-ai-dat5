#pragma once
#include "InformationEnums.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <BWAPI.h>
#include "BuildOrderPredictor.h"

class StrategyManager
{
public:
	static StrategyManager* GetInstance();
	void Update();
private:
	static bool initialized;
	InformationEnums::ThreatLevel currentThreatLevel;
	InformationEnums::Matchup matchup;
	static StrategyManager* strategyManager;
	StrategyManager();
};
