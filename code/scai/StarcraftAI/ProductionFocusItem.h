#pragma once
#include "Condition.h"
#include "BuildOrderItem.h"

class ProductionFocusItem:public BuildOrderItem
{
	std::list <Condition*> conditions;
	public:
		ProductionEnums::ProductionFocus productionFocus;
		ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,Condition* conditionToBeFulfilled);
		ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,std::list<Condition*> conditionsToBeFulFilled);
};
