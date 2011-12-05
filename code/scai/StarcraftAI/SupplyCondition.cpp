#include "SupplyCondition.h"

SupplyCondition::SupplyCondition(int supplyToReach)
{
	supply=supplyToReach;
}

bool SupplyCondition::IsFulfilled()
{
	if(supply<=BWAPI::Broodwar->self()->supplyUsed()/2)
	{
		return true;
	}
	return false;
}
