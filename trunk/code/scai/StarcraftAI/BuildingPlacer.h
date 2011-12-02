#pragma once
#include <BWAPI.h>

class BuildingPlacer
{
public:
	BuildingPlacer();
private:
	void Construct(BWAPI::UnitType buildingType);
};