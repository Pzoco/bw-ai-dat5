#include "UnitProductionCondition.h"
#include "TacticsManager.h"
#include "UnitHelper.h"

UnitProductionCondition::UnitProductionCondition(BWAPI::UnitType unitTypeToGet,int numberOfUnits)
{
	unitType = unitTypeToGet;
	number = numberOfUnits;
}
bool UnitProductionCondition::IsFulfilled()
{
	if(number==UnitHelper::GetNumberOfUnitType(unitType))
	{
		return true;
	}
	return false;
}