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
	std::list<ProductionTask*> GetProductionTasks();
private:
	BuildOrder* _currentBuildOrder;
	std::list<BuildOrder*> _availableBuildOrders;
	bool initiated;
	void InitiateBuildOrders();
	void SetCurrentBuildOrder();
	ProductionTask* CreateProductionTask(BuildOrderItem* item);
	void PrintBuildOrder(BuildOrder* buildorder);
	void RemoveItem(BuildOrderItem* item);
};
