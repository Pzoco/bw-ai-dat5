#include "StarcraftAI.h"
#include "UnitAgent.h"
using namespace BWAPI;

std::list<BWAPI::Unit*> _allUnits;
std::list<UnitAgent::UnitAgent> _agents;
//std::set<UnitAgent::UnitAgent*> _allUnitAgents;


void StarcraftAI::onStart()
{
	//_allUnits.push_front(Broodwar->self()->getUnits());
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	for(std::set<BWAPI::Unit*>::iterator k = myUnits.begin(); k != myUnits.end(); k++)
	{
		if((*k)->getType() == BWAPI::UnitTypes::Terran_SCV)
		{
			_agents.push_front(UnitAgent::UnitAgent((*k)));
		}
	}
}

void StarcraftAI::onEnd(bool isWinner)
{
	
}

void StarcraftAI::onFrame()
{
	for each(UnitAgent::UnitAgent agent in _agents)
	{
		
	}
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