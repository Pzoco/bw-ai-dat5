#include "UnitProductionItem.h"

UnitProductionItem::UnitProductionItem(BWAPI::UnitType unitToBeBuild,int numberOfUnits, Condition* conditionToBeFulfilled)
{
	unit = unitToBeBuild;
	number = numberOfUnits;
	conditions.push_back(conditionToBeFulfilled);
}			
UnitProductionItem::UnitProductionItem(BWAPI::UnitType unitToBeBuild,int numberOfUnits,std::list<Condition*> conditionsToBeFulFilled): unit(unitToBeBuild)
{
	unit = unitToBeBuild;
	number = numberOfUnits;
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}

}

std::string UnitProductionItem::GetType()
{
	return "UnitProductionItem";
}