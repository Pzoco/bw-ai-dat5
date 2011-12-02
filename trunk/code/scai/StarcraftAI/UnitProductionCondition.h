#pragma once
#include "ScoutingManager.h"
#include "Condition.h"
#include <BWAPI.h>

class UnitProductionCondition: public Condition
{
	public: 
		BWAPI::UnitType unitType; 
		int number;
		UnitProductionCondition(BWAPI::UnitType unitTypeToGet,int numberOfUnits);
		bool IsFulfilled();
};