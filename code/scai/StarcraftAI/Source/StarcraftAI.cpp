#include "StarcraftAI.h"
#include "../Squad.h"
#include "../BaseTactic.h"
#include "../TacticsManager.h"
#include "../ScoutingManager.h"
#include "../ProductionManager.h"
#include <BWAPI.h>
#include <BWTA.h>
#include "../ReinforcementLearning.h"

using namespace BWAPI;
TacticsManager tacticsManager;
ScoutingManager scoutingManager;
ProductionManager productionManager;
ReinforcementLearning reinforcementLearning = ReinforcementLearning();

void StarcraftAI::onStart()
{
	
	StarcraftAI::reinforcementLearning.LoadWeightsFromFile();
	//reinforcementLearning.OpenRewardFile();
	Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);

	//Creating a tacticsmanager and assigning the our units to squads
	tacticsManager = TacticsManager();
	tacticsManager.AssignToSquads(Broodwar->self()->getUnits());

	//Creates a scoutingmanager and analyzes the map
	scoutingManager = ScoutingManager();
	scoutingManager.AnalyzeMap()
		;
	//Creates a productionmanager and saves the scvs
	productionManager = ProductionManager();
	productionManager.AssignScvs(Broodwar->self()->getUnits());

}

void StarcraftAI::onEnd(bool isWinner)
{
	//reinforcementLearning.CloseRewardFile();
}

void StarcraftAI::onFrame()
{
	tacticsManager.Update();
	scoutingManager.Update();
	productionManager.Update(); 
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

void StarcraftAI::onUnitDiscover(BWAPI::Unit* unit)
{
  
}

void StarcraftAI::onUnitEvade(BWAPI::Unit* unit)
{
  
}

void StarcraftAI::onUnitShow(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitHide(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitCreate(BWAPI::Unit* unit)
{
	if(unit->getType() == BWAPI::UnitTypes::Terran_SCV)
	{
		productionManager.AssignScv(unit);
	}
	else
	{
		tacticsManager.AssignToSquad(unit);
	}
}

void StarcraftAI::onUnitDestroy(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitMorph(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitRenegade(BWAPI::Unit* unit)
{

}

void StarcraftAI::onSaveGame(std::string gameName)
{

}


