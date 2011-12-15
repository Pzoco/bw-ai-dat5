#include "StarcraftAI.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../TacticsManager.h"
#include "../ScoutingManager.h"
#include "../ProductionManager.h"
#include "../WorkerManager.h"
#include "../StrategyManager.h"
#include "math.h"


using namespace BWAPI;
int gameCount = 1;
ReinforcementLearning reinforcementLearning = ReinforcementLearning();

struct StarcraftAI::Thetas
{
	double ally;
	double squad;
	double mde;
	double edge;
	double cool;
} _thetas; 


void StarcraftAI::onStart()
{
	
	//Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);
	reinforcementLearning.LoadWeightsFromFile();
	//scoutingManager.AnalyzeMap();*/
}

void StarcraftAI::onEnd(bool isWinner)
{	

	/*StarcraftAI::reinforcementLearning.SaveCurrentWeightsToFile(); 

	gameCount++;
	BWAPI::Broodwar->restartGame();*/
}


void StarcraftAI::onFrame()
{
	
	TacticsManager::GetInstance()->Update();
	ScoutingManager::GetInstance()->Update();
	ProductionManager::GetInstance()->Update();
	WorkerManager::GetInstance()->Update();
	StrategyManager::GetInstance()->Update();

}

void StarcraftAI::onSendText(std::string text)
{

}

void StarcraftAI::onReceiveText(BWAPI::Player* player, std::string text)
{
	
}

void StarcraftAI::onPlayerLeft(BWAPI::Player* player)
{
 
}

void StarcraftAI::onNukeDetect(BWAPI::Position target)
{

}
void StarcraftAI::onUnitEvade(BWAPI::Unit* unit)
{
  
}

void StarcraftAI::onUnitShow(BWAPI::Unit* unit)
{
	
	if(unit->getPlayer() == BWAPI::Broodwar->self())
	{
		//Assigns the units to the different managers
		//!!!! THE UNITS ARE ONLY BEING PRODUCED/CONSTRUCTED !!!!
		if(UnitHelper::IsOffensiveType(unit->getType()))
		{
			TacticsManager::GetInstance()->AssignToSquad(unit);
		}
		else if(unit->getType() == BWAPI::UnitTypes::Terran_SCV )
		{
			WorkerManager::GetInstance()->ScvCreated(unit);
		}
		else if(unit->getType().isBuilding() && (unit->getType().canProduce() || UnitHelper::CanResearch(unit)))
		{
			ProductionManager::GetInstance()->BuildingConstructed(unit);
		}
	}
	else if(unit->getPlayer() == BWAPI::Broodwar->enemy())
	{
		ScoutingManager::GetInstance()->UnitFound(unit);
	}
}

void StarcraftAI::onUnitHide(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitCreate(BWAPI::Unit* unit)
{
}

void StarcraftAI::onUnitDestroy(BWAPI::Unit* unit)
{
	if(unit->getPlayer() == BWAPI::Broodwar->self())
	{
		//Assigns the units to the different managers
		if(UnitHelper::IsOffensiveType(unit->getType()))
		{
			TacticsManager::GetInstance()->UnitKilled(unit);
		}
		else if(unit->getType() == BWAPI::UnitTypes::Terran_SCV )
		{
			WorkerManager::GetInstance()->ScvKilled(unit);
		}
		else if(unit->getType().isBuilding() && unit->getType().canProduce())
		{
			ProductionManager::GetInstance()->BuildingDestroyed(unit);
		}
	}
}


