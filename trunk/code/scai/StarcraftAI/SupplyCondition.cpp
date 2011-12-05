#include "SupplyCondition.h"

SupplyCondition::SupplyCondition(int supplyToReach)
{
	supply=supplyToReach;
}

bool SupplyCondition::IsFulfilled()
{
	if(supply<=BWAPI::Broodwar->self()->supplyUsed())
	{
		return true;
	}
	return false;
}
