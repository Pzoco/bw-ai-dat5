#include "StarcraftAI.h"
#include "../Squad.h"
#include "../BaseTactic.h"
#include "../TacticsManager.h"
#include "../ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>

using namespace BWAPI;
TacticsManager tacticsManager;
ScoutingManager scoutingManager;


void StarcraftAI::onStart()
{
	Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);
	
	//Creating a tacticsmanager and assigning the our units to squads
	tacticsManager = TacticsManager();
	tacticsManager.AssignToSquads(Broodwar->self()->getUnits());

	scoutingManager = ScoutingManager();
	scoutingManager.AnalyzeMap();

}

void StarcraftAI::onEnd(bool isWinner)
{
	
}

void StarcraftAI::onFrame()
{
	tacticsManager.Update();
	scoutingManager.Update();
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


