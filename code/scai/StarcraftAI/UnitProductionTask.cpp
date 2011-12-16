#include "UnitProductionTask.h"

UnitProductionTask::UnitProductionTask(BWAPI::UnitType unitType, int numberOfUnits)
{
	unit = unitType;
	number = numberOfUnits;
}

std::string UnitProductionTask::GetType()
{
	return "UnitProductionTask";
}