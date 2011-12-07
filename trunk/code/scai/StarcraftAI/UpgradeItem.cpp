#include "UpgradeItem.h"

UpgradeItem::UpgradeItem(BWAPI::UpgradeType upgrade,Condition* conditionToBeFulfilled)
{
	upgradeType = upgrade;
	conditions.push_back(conditionToBeFulfilled);
	type = "UpgradeItem";
}
UpgradeItem::UpgradeItem(BWAPI::UpgradeType upgrade,std::list<Condition*> conditionsToBeFulFilled)
{
	upgradeType = upgrade;
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
	type = "UpgradeItem";
}