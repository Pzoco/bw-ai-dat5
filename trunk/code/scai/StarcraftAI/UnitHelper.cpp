#include "UnitHelper.h"

UnitHelper::UnitHelper(void)
{
}

BWAPI::Unit* UnitHelper::GetUnit(BWAPI::UnitType unitType)
{
	for each(BWAPI::Unit* unit in BWAPI::Broodwar->self()->getUnits())
	{
		if(unit->getType() == unitType)
		{
			return unit;
		}
	}
	//Wonder what this does
	return 0;
}
std::list<BWAPI::Unit*> UnitHelper::GetAllUnitsOfType(BWAPI::UnitType unitType)
{
	std::list<BWAPI::Unit*> units;
	for each(BWAPI::Unit* unit in BWAPI::Broodwar->self()->getUnits())
	{
		if(unit->getType() == unitType)
		{
			units.push_back(unit);
		}
	}
	return units;
}
std::list<BWAPI::Unit*> UnitHelper::GetBuildingsWhichCanProduce(BWAPI::UnitType unitType)
{
	BWAPI::UnitType buildingType = GetBuildingWhichCanProduce(unitType);
	std::list<BWAPI::Unit*> buildings;
	for each(BWAPI::Unit* unit in BWAPI::Broodwar->self()->getUnits())
	{
		if(unit->getType() == buildingType)
		{
			buildings.push_back(unit);
		}
	}
	return buildings;
}
int UnitHelper::GetNumberOfUnitType(BWAPI::UnitType unitType)
{
	//Could probably be a better way
	int count = 0;
	for each(BWAPI::Unit* unit in BWAPI::Broodwar->self()->getUnits())
	{
		if(unit->getType() == unitType && unit->isCompleted())
			count++;
	}
	//BWAPI::Broodwar->printf("There was %d of unittype %s",count,unitType.getName().c_str());
	return count;
}
BWAPI::UnitType UnitHelper::GetBuildingWhichCanProduce(BWAPI::UnitType unitType)
{
	if(unitType == BWAPI::UnitTypes::Terran_Marine || 
		unitType == BWAPI::UnitTypes::Terran_Firebat || 
		unitType == BWAPI::UnitTypes::Terran_Ghost)
	{
		return BWAPI::UnitTypes::Terran_Barracks;
	}
	else if(unitType == BWAPI::UnitTypes::Terran_Vulture || 
		unitType == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode || 
		unitType == BWAPI::UnitTypes::Terran_Goliath)
	{
		return BWAPI::UnitTypes::Terran_Factory;
	}
	return 0;
}
bool UnitHelper::IsOffensiveType(BWAPI::UnitType type)
{
	if(type.isBuilding() || type.isWorker())
	{
		return false;
	}
	return true;
}
BWAPI::UnitType UnitHelper::GetMainBuildingOfAddon(BWAPI::UnitType addon)
{
	if(addon == BWAPI::UnitTypes::Terran_Machine_Shop)
	{
		return BWAPI::UnitTypes::Terran_Factory;
	}
	else if(addon == BWAPI::UnitTypes::Terran_Comsat_Station)
	{
		return BWAPI::UnitTypes::Terran_Command_Center;
	}
	else if(addon == BWAPI::UnitTypes::Terran_Control_Tower)
	{
		return BWAPI::UnitTypes::Terran_Starport;
	}
	else if(addon == BWAPI::UnitTypes::Terran_Physics_Lab || 
		addon == BWAPI::UnitTypes::Terran_Covert_Ops)
	{
		return BWAPI::UnitTypes::Terran_Science_Facility;
	}
	return BWAPI::UnitTypes::None;
}
bool UnitHelper::CanResearch(BWAPI::Unit *building)
{
	BWAPI::UnitType type = building->getType();
	if(type == BWAPI::UnitTypes::Terran_Academy ||
		type == BWAPI::UnitTypes::Terran_Armory ||
		type == BWAPI::UnitTypes::Terran_Control_Tower ||
		type == BWAPI::UnitTypes::Terran_Covert_Ops ||
		type == BWAPI::UnitTypes::Terran_Engineering_Bay ||
		type == BWAPI::UnitTypes::Terran_Physics_Lab || 
		type == BWAPI::UnitTypes::Terran_Machine_Shop)
	{
		return true;
	}
	return false;
}