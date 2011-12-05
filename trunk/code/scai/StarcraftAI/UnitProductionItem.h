#pragma once
#include "BuildOrderItem.h"
#include "Condition.h"
#include <BWAPI.h>

class UnitProductionItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType unit;
		UnitProductionItem(BWAPI::UnitType unitToBeBuild, Condition* conditionToBeFulfilled);
		UnitProductionItem(BWAPI::UnitType unitToBeBuild,std::list<Condition*> conditionsToBeFulFilled);
};
