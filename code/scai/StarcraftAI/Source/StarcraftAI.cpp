#include "StarcraftAI.h"
#include "../Squad.h"
#include "../BaseTactic.h"
#include "../TacticsManager.h"
using namespace BWAPI;

TacticsManager tacticsManager;

void StarcraftAI::onStart()
{
	
	Broodwar->enableFlag(Flag::UserInput);
	tacticsManager = TacticsManager();
	tacticsManager.AssignToSquads(Broodwar->self()->getUnits());

}

void StarcraftAI::onEnd(bool isWinner)
{
	
}

void StarcraftAI::onFrame()
{
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	for(std::set<BWAPI::Unit*>::const_iterator k = myUnits.begin(); k != myUnits.end(); k++)
	{
		BaseTactic tac;
		tac.ExecuteTactic((*k),myUnits);
		
		
	}
	//tacticsManager.Update();
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
