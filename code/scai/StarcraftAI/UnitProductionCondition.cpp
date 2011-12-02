#include "UnitProductionCondition.h"
#include "TacticsManager.h"

UnitProductionCondition::UnitProductionCondition(BWAPI::UnitType unitTypeToGet,int numberOfUnits)
{
	unitType = unitTypeToGet;
}
bool UnitProductionCondition::IsFulfilled()
{
	if(number==TacticsManager::GetNumberOfUnits(unitType))
	{
		return true;
	}
	return false;
}