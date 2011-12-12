#include "ScoutItem.h"

ScoutItem::ScoutItem(Condition* conditionToBeFulfilled)
{
	conditions.push_back(conditionToBeFulfilled);
	type = "ScoutItem";
}
ScoutItem::ScoutItem(std::list<Condition*> conditionsToBeFulFilled)
{
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
	type = "ScoutItem";
}

