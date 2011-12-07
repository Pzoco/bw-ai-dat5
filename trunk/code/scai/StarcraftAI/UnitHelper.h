#pragma once
#include <BWAPI.h>

class UnitHelper
{
public:
	UnitHelper(void);
	static BWAPI::Unit* GetUnit(BWAPI::UnitType unitType);
	static std::list<BWAPI::Unit*> GetAllUnitsOfType(BWAPI::UnitType unitType);
	static std::list<BWAPI::Unit*> GetBuildingsWhichCanProduce(BWAPI::UnitType buildingType);
	static BWAPI::UnitType GetBuildingWhichCanProduce(BWAPI::UnitType buildingType);
	static int GetNumberOfUnitType(BWAPI::UnitType unitType);
	static bool IsOffensiveType(BWAPI::UnitType unitType);
	static bool IsBuilding(BWAPI::UnitType unitType);
	static BWAPI::UnitType GetMainBuildingOfAddon(BWAPI::UnitType addon);
	static bool CanResearch(BWAPI::Unit* building);
};
