#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"

class ProductionManager
{
public:
	enum BuildingState{BeingConstructed,Producing,NotProducing};
	ProductionManager();
	void BuildingConstructed(BWAPI::Unit* building);
	void SetProductionFocus(ProductionEnums::ProductionFocus focus);
	void Update();
private:
	void TryProduceUnit(UnitProductionTask task);
	void TryConstructBuilding(ConstructionTask task);
	void TryResearchTech(ResearchTask task);
	void RemoveTask(ProductionTask task);
};
