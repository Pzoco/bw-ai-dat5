#pragma once
#include "BuildOrderItem.h"
#include "Condition.h"
#include <BWAPI.h>

class UnitProductionItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType unit;
		int number;
		UnitProductionItem(BWAPI::UnitType unitToBeBuild,int numberOfUnits, Condition* conditionToBeFulfilled);
		UnitProductionItem(BWAPI::UnitType unitToBeBuild,int numberOfUnits,std::list<Condition*> conditionsToBeFulFilled);
		std::string GetType();
};
