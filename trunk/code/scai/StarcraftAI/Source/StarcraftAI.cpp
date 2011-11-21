#include "StarcraftAI.h"
#include "../Squad.h"
#include "../BaseTactic.h"
#include "../TacticsManager.h"
#include <BWAPI.h>
#include <BWTA.h>
using namespace BWAPI;
bool analyzed;

TacticsManager tacticsManager;

void StarcraftAI::onStart()
{
	Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);
	BWTA::readMap();
	BWTA::analyze();

	tacticsManager = TacticsManager();
	tacticsManager.AssignToSquads(Broodwar->self()->getUnits());

	/*Squad s;
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	for(std::set<BWAPI::Unit*>::const_iterator k = myUnits.begin(); k != myUnits.end(); k++)
	{
		s.AddUnit((*k));	
	}
	BWAPI::Broodwar->printf("size: %d",s.GetSize());*/
}

void StarcraftAI::onEnd(bool isWinner)
{
	
}

void StarcraftAI::onFrame()
{
	tacticsManager.Update();
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
