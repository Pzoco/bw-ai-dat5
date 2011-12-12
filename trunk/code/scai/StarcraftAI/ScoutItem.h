#pragma once

#include "BuildOrderItem.h"
#include <BWAPI.h>

class ScoutItem: public BuildOrderItem
{
public: 
	ScoutItem(Condition* conditionToBeFulfilled);
	ScoutItem(std::list<Condition*> conditionsToBeFulFilled);
};	