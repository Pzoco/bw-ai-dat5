#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"
#include "BuildOrderItem.h"
#include "ProductionTask.h"
#include "Condition.h"
#include "ConstructionTask.h"
#include "UnitProductionTask.h"
#include "ProductionFocusTask.h"
#include "ResearchTask.h"

class BuildOrderHandler
{
public:
	BuildOrderHandler(void);
	void Update();
	std::list<UnitProductionTask*> GetUnitProductionTasks(){return unitProductionTasks;}
	std::list<ConstructionTask*> GetConstructionTasks(){return constructionTasks;}
	std::list<ProductionFocusTask*> GetProductionFocusTasks(){return productionFocusTasks;}
	std::list<ResearchTask*> GetResearchTasks(){return researchTasks;}
private:
	BuildOrder* _currentBuildOrder;
	std::list<BuildOrder*> _availableBuildOrders;
	std::list<UnitProductionTask*> unitProductionTasks;
	std::list<ProductionFocusTask*> productionFocusTasks;
	std::list<ResearchTask*> researchTasks;
	std::list<ConstructionTask*> constructionTasks;
	bool initiated;
	void InitiateBuildOrders();
	void SetCurrentBuildOrder();
	void SaveAsTask(BuildOrderItem* item);
	void PrintBuildOrder(BuildOrder* buildorder);
};
