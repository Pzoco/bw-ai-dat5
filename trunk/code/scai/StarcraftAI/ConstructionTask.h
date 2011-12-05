#pragma once
#include "ProductionTask.h"
#include <BWAPI.h>
class ConstructionTask: public ProductionTask
{
public:
	BWAPI::UnitType building;
	ProductionEnums::BuildingPlacement placement;
	ConstructionTask(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement);
	std::string GetType();
};