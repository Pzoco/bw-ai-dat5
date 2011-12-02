#pragma once
#include <BWAPI.h>
#include "Condition.h"

class SupplyCondition: public Condition
{
public:	
	int supply;
	SupplyCondition(int supplyToReach);
	bool IsFulfilled();
};