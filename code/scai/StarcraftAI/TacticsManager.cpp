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

std::list<Squad> TacticsManager::GetRightSquadList(BWAPI::UnitType unitType)
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
/*
	The following is a possible solution to the bug in AssignToSquad.
	Before it only got a copy of the list, so if the list was empty and 
	you tried to add something, you would just add it to a copy of the
	list, and then never save it. This is just a function that saves it.

	It should be possible to get it to work by returning a pointer to the
	correct list like:
	std::list<Squad> * TacticsManager::GetRightSquadList(BWAPI::UnitType unitType)
	{
		if(unitType == BWAPI::UnitTypes::Terran_Vulture){std::list<Squad> *squad = &_vultureSquads; return squad;}
		...
	}
	But havnt gotten that solution to work.

*/
void TacticsManager::WriteSquadList(BWAPI::UnitType unitType, std::list<Squad> list)
{
	if(unitType == BWAPI::UnitTypes::Terran_Vulture){_vultureSquads = list;}
	else if(unitType == BWAPI::UnitTypes::Terran_Marine) { _marineSquads = list; }
	else if(unitType == BWAPI::UnitTypes::Terran_Medic) { _medicSquads = list; }
	else if(unitType == BWAPI::UnitTypes::Terran_Wraith) { _wraithSquads = list;}
	else if(unitType == BWAPI::UnitTypes::Terran_Goliath) { _golliathSquads = list;}
	else if(unitType == BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode) { _tankSquads = list;}
	else if(unitType == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode) { _tankSquads = list;}
}
void TacticsManager::AddSquad(Squad squad)
{
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
	if(!IsSquadType(unit->getType()))
	{
		return;
	}
	std::list<Squad> squads = GetRightSquadList(unit->getType());
	if(squads.empty())
	{
		//Should use the specific tactic not basetactic
		Squad s = Squad(unit,BaseTactic());
		squads.push_back(s);
		WriteSquadList(unit->getType(),squads);
	}
	else
	{
		//Improve this in the future
		squads.front().AddUnit(unit);
	}
}
void TacticsManager::AssignToSquads(std::set<BWAPI::Unit*> units)
{
	for each(BWAPI::Unit* unit in units)
	{
		AssignToSquad(unit);
	}
}

bool TacticsManager::IsSquadType(BWAPI::UnitType type)
{
	if(type == BWAPI::UnitTypes::Terran_SCV || 
		type == BWAPI::UnitTypes::Terran_Command_Center || 
		type == BWAPI::UnitTypes::Terran_Academy || 
		type == BWAPI::UnitTypes::Terran_Command_Center || 
		type == BWAPI::UnitTypes::Terran_Armory ||
		type == BWAPI::UnitTypes::Terran_Barracks || 
		type == BWAPI::UnitTypes::Terran_Bunker || 
		type == BWAPI::UnitTypes::Terran_Comsat_Station || 
		type == BWAPI::UnitTypes::Terran_Control_Tower ||
		type == BWAPI::UnitTypes::Terran_Covert_Ops || 
		type == BWAPI::UnitTypes::Terran_Engineering_Bay ||
		type == BWAPI::UnitTypes::Terran_Missile_Turret || 
		type == BWAPI::UnitTypes::Terran_Machine_Shop ||
		type == BWAPI::UnitTypes::Terran_Nuclear_Silo || 
		type == BWAPI::UnitTypes::Terran_Physics_Lab ||
		type == BWAPI::UnitTypes::Terran_Refinery || 
		type == BWAPI::UnitTypes::Terran_Science_Facility ||
		type == BWAPI::UnitTypes::Terran_Starport || 
		type == BWAPI::UnitTypes::Terran_Supply_Depot ||
		type == BWAPI::UnitTypes::Terran_Vulture_Spider_Mine || 
		type == BWAPI::UnitTypes::Terran_Nuclear_Missile)
	{
		return false;
	}
	return true;
}
int TacticsManager::GetNumberOfUnits(BWAPI::UnitType type)
{
	if(IsSquadType(type))
	{
		std::list<Squad> squads = GetRightSquadList(type);
		int number= 0;
		for each(Squad squad in squads)
		{
			number+=squad.GetSize();
		}
		return 0;
	}
	return 0;
}