#include "AttackItem.h"

AttackItem::AttackItem(Condition* conditionToBeFulfilled)
{
	conditions.push_back(conditionToBeFulfilled);
	type = "AttackItem";
}
AttackItem::AttackItem(std::list<Condition*> conditionsToBeFulFilled)
{
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
	type = "AttackItem";
}