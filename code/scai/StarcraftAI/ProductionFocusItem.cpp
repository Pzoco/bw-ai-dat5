#include "ProductionFocusItem.h"

ProductionFocusItem::ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,Condition* conditionToBeFulfilled)
{
	productionFocus = productionFocusToBeFulfilled;
	conditions.push_back(conditionToBeFulfilled);
	type = "ProductionFocusItem";
}
ProductionFocusItem::ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,std::list<Condition*> conditionsToBeFulFilled)
{
	productionFocus = productionFocusToBeFulfilled;
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
	type = "ProductionFocusItem";
}
