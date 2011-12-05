#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"
#include "UnitProductionTask.h"
#include "ConstructionTask.h"
#include "ResearchTask.h" 
#include "ProductionFocusTask.h"

class ProductionManager
{
public:
	enum BuildingState{BeingConstructed,Producing,NotProducing};
	ProductionManager();
	void BuildingConstructed(BWAPI::Unit* building);
	void BuildingDestroyed(BWAPI::Unit* building);
	void SetProductionFocus(ProductionEnums::ProductionFocus focus);
	void Update();
private:
	std::list<ConstructionTask*> _constructionTasks;
	std::list<UnitProductionTask*> _unitProductionTasks;
	std::list<ResearchTask*> _researchTasks;
	std::list<ProductionFocusTask*> _productionFocusTasks;
	void RetrieveTasks();
	bool TryProduceUnit(UnitProductionTask* task);
	bool TryConstructBuilding(ConstructionTask* task);
	bool TryResearchTech(ResearchTask* task);
};
