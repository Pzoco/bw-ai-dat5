#pragma once
#include <BWAPI.h>
#include "ProductionEnums.h"
#include "InformationEnums.h"

class BuildingPlacementFinder
{
public:
	BuildingPlacementFinder();
	bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const;
	bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const;
	bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const;
	BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type) const;
	BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const;
	BWAPI::TilePosition GetClosestGasGeyser(BWAPI::TilePosition position);
	BWAPI::TilePosition FindBuildLocation(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement);
private:
	int buildMap[30][30];
	int buildDistance;
	BWAPI::TilePosition myBaseTile;
	BWAPI::Position myBasePosition;
	InformationEnums::Positions myBaseEnum;
	static const int BASE_TILES = 30;
	bool initialized;
	
};