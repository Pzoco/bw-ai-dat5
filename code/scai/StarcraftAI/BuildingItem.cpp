#include "BuildingItem.h"
#include "Condition.h"
#include <BWAPI.h>

BuildingItem::BuildingItem(BWAPI::UnitType buildingToBeBuild,ProductionEnums::BuildingPlacement buildingPlacement,Condition* conditionToBeFulfilled)
{
	building = buildingToBeBuild;
	this->buildingPlacement = buildingPlacement;
	conditions.push_back(conditionToBeFulfilled);
	type = "BuildingItem";
}
BuildingItem::BuildingItem(BWAPI::UnitType buildingToBeBuild,ProductionEnums::BuildingPlacement buildingPlacement,std::list<Condition*> conditionsToBeFulFilled)
{
	building = buildingToBeBuild;
	this->buildingPlacement = buildingPlacement;
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
	type = "BuildingItem";
}
