#include "ConstructionTask.h"

ConstructionTask::ConstructionTask(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement)
{
	building = buildingType;
	buildingPlacement = placement;
	mineralPrice = building.mineralPrice();
	gasPrice = building.gasPrice();
}

std::string ConstructionTask::GetType()
{
	return "ConstructionTask";
}