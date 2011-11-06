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
	if(unitType == BWAPI::UnitTypes::Terran_Vulture){return _vultureSquads;}
	else if(unitType == BWAPI::UnitTypes::Terran_Marine) { return _marineSquads; }
	else if(unitType == BWAPI::UnitTypes::Terran_Medic) { return _medicSquads; }
	else if(unitType == BWAPI::UnitTypes::Terran_Wraith) { return _wraithSquads;}
	else if(unitType == BWAPI::UnitTypes::Terran_Goliath) { return _golliathSquads;}
	else if(unitType == BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode) { return _tankSquads;}
	else if(unitType == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode) { return _tankSquads;}

	//Dont do this :D
	return _vultureSquads;
}
void TacticsManager::Update()
{
	for each(Squad squad in _vultureSquads)
	{
		squad.ExecuteTactics();
	}
	for each(Squad squad in _marineSquads)
	{
		squad.ExecuteTactics();
	}
	for each(Squad squad in _medicSquads)
	{
		squad.ExecuteTactics();
	}
	for each(Squad squad in _wraithSquads)
	{
		squad.ExecuteTactics();
	}
	for each(Squad squad in _golliathSquads)
	{
		squad.ExecuteTactics();
	}
	for each(Squad squad in _tankSquads)
	{
		squad.ExecuteTactics();
	}
}


void AssignToSquad(BWAPI::Unit* unit)
{
	if(unit->getType() == BWAPI::UnitTypes::Terran_SCV || unit->getType() == BWAPI::UnitTypes::Buildings)
	{
		return;
	}
	std::list<Squad> squads = GetRightSquadList(unit->getType());
	if(squads.empty())
	{
		//Should use the specific tactic not basetactic
		Squad s = Squad(unit,BaseTactic());
		squads.push_back(s);
	}
	else
	{
		//Improve this in the future
		squads.front().AddUnit(unit);
	}
}
void AssignToSquads(std::set<BWAPI::Unit*> units)
{
	for each(BWAPI::Unit* unit in units)
	{
		AssignToSquad(unit);
	}
}




