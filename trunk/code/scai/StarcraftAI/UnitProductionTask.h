#pragma once
#include <BWAPI.h>
#include "ProductionTask.h"
class UnitProductionTask: public ProductionTask
{
public:
	BWAPI::UnitType unit;
	std::map<BWAPI::UnitType,int> requiredBuildings;
	UnitProductionTask(BWAPI::UnitType unitType);
	std::string GetType();
};