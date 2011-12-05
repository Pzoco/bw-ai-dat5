#include "ResearchItem.h"

ResearchItem::ResearchItem(BWAPI::TechType tech,Condition* conditionToBeFulfilled)
{
	techType = tech;
	conditions.push_back(conditionToBeFulfilled);
}
ResearchItem::ResearchItem(BWAPI::TechType tech,std::list<Condition*> conditionsToBeFulFilled)
{
	techType = tech;
	for each(Condition* c in conditionsToBeFulFilled)
	{
		conditions.push_back(c);
	}
}
std::string ResearchItem::GetType()
{
	return "ResearchItem";
}