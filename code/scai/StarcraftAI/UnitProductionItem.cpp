#include "UnitProductionItem.h"

UnitProductionItem::UnitProductionItem(BWAPI::UnitType unitToBeBuild, Condition* conditionToBeFulfilled)
{
	unit = unitToBeBuild;
	conditions.push_back(conditionToBeFulfilled);
}			
UnitProductionItem::UnitProductionItem(BWAPI::UnitType unitToBeBuild,std::list<Condition*> conditionsToBeFulFilled): unit(unitToBeBuild)
{
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
}

std::string UnitProductionItem::GetType()
{
	return "UnitProductionItem";
}