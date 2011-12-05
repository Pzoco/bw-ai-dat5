#include "UnitProductionTask.h"

UnitProductionTask::UnitProductionTask(BWAPI::UnitType unitType)
{
	unit = unitType;
	mineralPrice = unit.mineralPrice();
	gasPrice = unit.gasPrice();
	requiredBuildings = unit.requiredUnits();
}

std::string UnitProductionTask::GetType()
{
	return "UnitProductionTask";
}