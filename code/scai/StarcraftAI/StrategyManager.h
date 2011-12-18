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
	BWAPI::Position EnemieBasePosision;
	void NewEnemyFound(BWAPI::Unit* unit);
	void Update();
private:
	static bool initialized;
	std::list<BWAPI::Unit*> enemyUnits;
	InformationEnums::ThreatLevel currentThreatLevel;
	InformationEnums::Matchup matchup;
	static StrategyManager* strategyManager;
	StrategyManager();

};
