#include "TacticsManager.h"
#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>

std::list<Squad> _vultureSquads;
std::list<Squad> _marineSquads;
std::list<Squad> _medicSquads;
std::list<Squad> _wraithSquads;
std::list<Squad> _golliathSquads;
std::list<Squad> _tankSquads;


TacticsManager::TacticsManager(void)
{

}

std::list<Squad> GetRightSquadList(BWAPI::UnitType unitType)
{
	switch(unitType)
	{
		case BWAPI::UnitTypes::Terran_Vulture : return _vultureSquads;
		case BWAPI::UnitTypes::Terran_Marine : return _marineSquads;
		case BWAPI::UnitTypes::Terran_Medic : return _medicSquads;
		case BWAPI::UnitTypes::Terran_Wraith : return _wraithSquads;
		case BWAPI::UnitTypes::Terran_Goliath : return _golliathSquads;
		case BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode : return _tankSquads;
		case BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode : return _tankSquads;
	}
	//Will probably crash if not matched!
	return;
}
void TacticsManager::Update()
{
	for each(Squad squad in _squads)
	{
		squad.ExecuteTactics();
	}
}


void AssignToSquad(BWAPI::Unit* unit)
{
	if(unit->getType() == BWAPI::UnitTypes::Terran_SCV)
	{
		continue;
	}
	std::list<Squad> squads = GetRightSquad(unit->getType());
	if(squads.empty())
	{
		squads.push_back(Squad(unit));
	}
}
void AssignToSquads(std::list<BWAPI::Unit*> units)
{
	for each(BWAPI::Unit* unit in units)
	{
		AssignToSquad(unit);
	}
}




