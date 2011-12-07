#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"
#include "UnitProductionTask.h"
#include "ConstructionTask.h"
#include "UpgradeTask.h" 
#include "ResearchTask.h"
#include "ProductionFocusTask.h"

class ProductionManager
{
public:
	enum BuildingState{BeingConstructed,Producing,NotProducing};
	static ProductionManager* GetInstance();
	static void BuildingConstructed(BWAPI::Unit* building);
	static void BuildingDestroyed(BWAPI::Unit* building);
	void SetProductionFocus(ProductionEnums::ProductionFocus focus);
	void Update();
private:
	ProductionManager();
	static ProductionManager* productionManager;
	std::list<ConstructionTask*> _constructionTasks;
	std::list<UnitProductionTask*> _unitProductionTasks;
	std::list<ResearchTask*> _researchTasks;
	std::list<UpgradeTask*> _upgradeTasks;
	std::list<ProductionFocusTask*> _productionFocusTasks;
	bool instanceInstantiated;
	void RetrieveTasks();
	bool TryProduceUnit(UnitProductionTask* task);
	bool TryConstructBuilding(ConstructionTask* task);
	bool TryUpgradeTech(UpgradeTask* task);
	bool TryResearchTech(ResearchTask* task);
};
