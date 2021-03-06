#pragma once
#include <BWAPI.h>
#include "BuildOrder.h"
#include "BuildOrderItem.h"
#include "ProductionTask.h"
#include "Condition.h"
#include "ConstructionTask.h"
#include "UnitProductionTask.h"
#include "ProductionFocusTask.h"
#include "UpgradeTask.h"
#include "ResearchTask.h"
#include "ScoutingManager.h"

class BuildOrderHandler
{
public:
	BuildOrderHandler(void);
	void Update();
	std::list<UnitProductionTask*> GetUnitProductionTasks()
	{
		std::list<UnitProductionTask*> returnList; 
		returnList.merge(unitProductionTasks);
		return returnList;
	}
	std::list<ConstructionTask*> GetConstructionTasks()
	{
		std::list<ConstructionTask*> returnList; 
		returnList.merge(constructionTasks);
		return returnList;
	}
	std::list<ProductionFocusTask*> GetProductionFocusTasks()
	{
		std::list<ProductionFocusTask*> returnList; 
		returnList.merge(productionFocusTasks);
		return returnList;
	}
	std::list<ResearchTask*> GetResearchTasks()
	{
		std::list<ResearchTask*> returnList; 
		returnList.merge(researchTasks);
		return returnList;
	}
	std::list<UpgradeTask*> GetUpgradeTasks()
	{
		std::list<UpgradeTask*> returnList; 
		returnList.merge(upgradeTasks);
		return returnList;
	}
private:
	BuildOrder* _currentBuildOrder;
	std::list<BuildOrder*> _availableBuildOrders;
	std::list<UnitProductionTask*> unitProductionTasks;
	std::list<ProductionFocusTask*> productionFocusTasks;
	std::list<UpgradeTask*> upgradeTasks;
	std::list<ResearchTask*> researchTasks;
	std::list<ConstructionTask*> constructionTasks;
	bool initiated;
	void InitiateBuildOrders();
	void SetCurrentBuildOrder();
	void SaveAsTask(BuildOrderItem* item);
	void PrintBuildOrder(BuildOrder* buildorder);
};
