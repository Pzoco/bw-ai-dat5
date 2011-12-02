#pragma once
#include <BWAPI.h>

class BuildingPlacer
{
public:
	BuildingPlacer();
	bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const;
	bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const;
	bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const;
	BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type) const;
	BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const;
	void Construct(BWAPI::UnitType buildingType);
private:
	int buildDistance;
};