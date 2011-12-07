#include "UnitProductionTask.h"

UnitProductionTask::UnitProductionTask(BWAPI::UnitType unitType)
{
	unit = unitType;
}

std::string UnitProductionTask::GetType()
{
	return "UnitProductionTask";
}