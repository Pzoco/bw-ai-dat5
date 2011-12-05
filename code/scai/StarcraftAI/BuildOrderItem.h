 #pragma once
#include <BWAPI.h>
#include "ProductionTask.h"
#include "ScoutingManager.h"
#include "TacticsManager.h"
#include "Condition.h"

//The items in the build order - There is a constructor for adding one condition or a list
class BuildOrderItem
{
	public:
		std::list<Condition*> GetConditions();
		virtual std::string GetType();
	protected:
		std::list <Condition*> conditions;
		std::string type;
};
