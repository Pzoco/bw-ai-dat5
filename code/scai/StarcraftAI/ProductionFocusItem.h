#pragma once
#include "Condition.h"
#include "BuildOrderItem.h"

class ProductionFocusItem:public BuildOrderItem
{
	public:
		ProductionEnums::ProductionFocus productionFocus;
		ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,Condition* conditionToBeFulfilled);
		ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,std::list<Condition*> conditionsToBeFulFilled);
};
