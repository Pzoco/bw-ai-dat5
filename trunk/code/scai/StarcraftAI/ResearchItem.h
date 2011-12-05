#pragma once
#include "BuildOrderItem.h"
#include <BWAPI.h>

class ResearchItem: public BuildOrderItem
{
	public: 
		BWAPI::TechType techType;
		ResearchItem(BWAPI::TechType tech,Condition* conditionToBeFulfilled);
		ResearchItem(BWAPI::TechType tech,std::list<Condition*> conditionsToBeFulFilled);
		std::string GetType();
};	