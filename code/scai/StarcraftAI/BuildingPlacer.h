#pragma once
#include <BWAPI.h>
class BuildingPlacer
{
public:
	BuildingPlacer(void);
	enum Placement {Base,MainChoke};
	void AddScv(BWAPI::Unit* unit);
	void Construct(BWAPI::UnitType buildingType,Placement);
};
