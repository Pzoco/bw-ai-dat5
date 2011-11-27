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

bool UnitHelper::IsBuilding(BWAPI::UnitType type)
{
	return false;
}