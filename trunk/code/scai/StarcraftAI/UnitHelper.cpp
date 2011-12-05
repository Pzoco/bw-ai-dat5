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