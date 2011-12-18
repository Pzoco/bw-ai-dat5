#pragma once
#include "BuildOrderItem.h"
#include "Condition.h"

class AttackItem: public BuildOrderItem
{
	public: 
		AttackItem(Condition* conditionToBeFulfilled);
		AttackItem(std::list<Condition*> conditionsToBeFulFilled);
};
