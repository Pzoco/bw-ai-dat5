#include "TacticsManager.h"
#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>
#include "UnitHelper.h"

std::list<Squad> _vultureSquads;
std::list<Squad> _marineSquads;
std::list<Squad> _medicSquads;
std::list<Squad> _wraithSquads;
std::list<Squad> _golliathSquads;
std::list<Squad> _tankSquads;


TacticsManager::TacticsManager(void)
{

}

std::list<Squad>& TacticsManager::GetRightSquadList(BWAPI::UnitType unitType)
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
void TacticsManager::AddSquad(Squad squad)
{
	_vultureSquads.push_front(squad);
}
void TacticsManager::RemoveSquad(Squad squad)
{

}
void TacticsManager::Update()
{
	for each(Squad squad in _vultureSquads)
	{
		squad.ExecuteTactics();
	}
	/*
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
	}*/
}
void TacticsManager::AssignToSquad(BWAPI::Unit* unit)
{
	if(UnitHelper::IsOffensiveType(unit->getType()))
	{
		std::list<Squad> &squads = GetRightSquadList(unit->getType());
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
}
void TacticsManager::AssignToSquads(std::set<BWAPI::Unit*> units)
{
	for each(BWAPI::Unit* unit in units)
	{
		AssignToSquad(unit);
	}
}


int TacticsManager::GetNumberOfUnits(BWAPI::UnitType type)
{
	if(UnitHelper::IsOffensiveType(type))
	{
		std::list<Squad> squads = GetRightSquadList(type);
		int number= 0;
		for each(Squad squad in squads)
		{
			number+=squad.GetSize();
		}
		return number;
	}
	return 0;
}