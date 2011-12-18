#pragma once
#include <BWAPI.h>
#include "ProductionEnums.h"
#include "InformationEnums.h"

class BuildingPlacementFinder
{
public:
	BuildingPlacementFinder();
	BWAPI::TilePosition FindBuildLocation(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement);
private:
	int buildMap[30][30];
	int buildDistance;
	BWAPI::TilePosition myBaseTile;
	BWAPI::Position myBasePosition;
	std::map<BWAPI::UnitType,std::list<BWAPI::TilePosition>> buildingPositions;
	InformationEnums::Positions myBaseEnum;
	static const int BASE_TILES = 30;
	bool initialized;
	bool OverlapInBuildingPlacement(BWAPI::UnitType type1, BWAPI::UnitType type2);
	bool BuildingOverlapOthers(BWAPI::TilePosition position2, BWAPI::UnitType type2);
	void SaveBarracksPositions();
	void SaveFactoriesPositions();
	void SaveSupplyDepotPositions();
	bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) ;
	bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type);
	bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist);
	BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type);
	BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist);
	BWAPI::TilePosition GetClosestGasGeyser(BWAPI::TilePosition position);
};