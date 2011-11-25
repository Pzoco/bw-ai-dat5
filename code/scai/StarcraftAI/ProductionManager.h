#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"

class ProductionManager
{
public:
	ProductionManager();
private:
	void Update();
	void InitiateBuildOrders();
	void SetCurrentBuildOrder();
	void ProduceUnit(BWAPI::UnitType unitType);
	void ConstructBuilding(BWAPI::UnitType buildingType);
	void ResearchTech(BWAPI::TechType techType);
};
