#pragma once
#include "BuildOrder.h"
#include "BuildOrderItem.h"
#include "ProductionTask.h"
#include "Condition.h"

class BuildOrderHandler
{
public:
	BuildOrderHandler(void);
	std::list<ProductionTask> GetProductionTasks();
private:
	void InitiateBuildOrders();
	void SetCurrentBuildOrder();
	ProductionTask CreateProductionTask(BuildOrderItem item);
	void PrintBuildOrder(BuildOrder buildorder);
};
