#pragma once
#include <BWAPI.h>
#include "ProductionTask.h"
class UnitProductionTask: public ProductionTask
{
public:
	BWAPI::UnitType unit;
	int number;
	std::map<BWAPI::UnitType,int> requiredBuildings;
	UnitProductionTask(BWAPI::UnitType unitType,int numberOfUnits);
	std::string GetType();
};