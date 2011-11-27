#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"

class ProductionManager
{
public:
	ProductionManager();
	void AssignScv(BWAPI::Unit* unit);
	void AssignScvs(std::set<BWAPI::Unit*> units);
	void Update();
private:
	void InitiateBuildOrders();
	void SetCurrentBuildOrder();
	void ProduceUnit(BWAPI::UnitType unitType);
	void ConstructBuilding(BWAPI::UnitType buildingType);
	void ResearchTech(BWAPI::TechType techType);
	void TryBuildSCV();
};
