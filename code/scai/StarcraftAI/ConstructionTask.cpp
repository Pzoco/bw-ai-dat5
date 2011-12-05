#include "ConstructionTask.h"

ConstructionTask::ConstructionTask(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement)
{
	building = buildingType;
	buildingPlacement = placement;
}

std::string ConstructionTask::GetType()
{
	return "ConstructionTask";
}