#pragma once
#include "BuildOrderItem.h"
#include <BWAPI.h>

class UpgradeItem: public BuildOrderItem
{
	public: 
		BWAPI::UpgradeType upgradeType;
		UpgradeItem(BWAPI::UpgradeType upgrade,Condition* conditionToBeFulfilled);
		UpgradeItem(BWAPI::UpgradeType upgrade,std::list<Condition*> conditionsToBeFulFilled);
};	