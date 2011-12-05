#pragma once
#include "BuildOrderItem.h"
#include "Condition.h"
#include <BWAPI.h>

class BuildingItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType building;
		ProductionEnums::BuildingPlacement buildingPlacement;
		BuildingItem(BWAPI::UnitType buildingToBeBuild,ProductionEnums::BuildingPlacement buildingPlacement,Condition* conditionToBeFulfilled);
		BuildingItem(BWAPI::UnitType buildingToBeBuild,ProductionEnums::BuildingPlacement buildingPlacement,std::list<Condition*> conditionsToBeFulFilled);
};

