#include "BuildOrderHandler.h"
#include "BuildOrder.h"
#include "Condition.h"
#include "UnitProductionCondition.h"
#include "BuildOrderItem.h"
#include "UpgradeItem.h"
#include "BuildingItem.h"
#include "UnitProductionItem.h"
#include "ProductionFocusItem.h"
#include "SupplyCondition.h"
#include "ProductionTask.h"
#include "ResearchItem.h"
#include "ScoutItem.h"


BuildOrderHandler::BuildOrderHandler(void)
{
	initiated =false;
}

void BuildOrderHandler::InitiateBuildOrders()
{
	BuildOrder* twoFactVultures =new BuildOrder("Two Fact Vulture");
	twoFactVultures->AddItem(new ProductionFocusItem(ProductionEnums::Focus_Workers,new SupplyCondition(4)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Supply_Depot,ProductionEnums::Placement_MainBase,new SupplyCondition(8)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Barracks,ProductionEnums::Placement_MainBase,new SupplyCondition(11)));
	twoFactVultures->AddItem(new ScoutItem(new SupplyCondition(11)));
	twoFactVultures->AddItem(new UnitProductionItem(BWAPI::UnitTypes::Terran_Marine,1,new SupplyCondition(11)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Refinery,ProductionEnums::Placement_MainBase,new SupplyCondition(11)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Supply_Depot,ProductionEnums::Placement_MainBase,new SupplyCondition(15)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Factory,ProductionEnums::Placement_MainBase,new SupplyCondition(15)));
	twoFactVultures->AddItem(new UnitProductionItem(BWAPI::UnitTypes::Terran_Vulture,1,new Condition()));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Machine_Shop,ProductionEnums::Placement_MainBase,new UnitProductionCondition(BWAPI::UnitTypes::Terran_Vulture,1)));
	twoFactVultures->AddItem(new UnitProductionItem(BWAPI::UnitTypes::Terran_Vulture,6,new UnitProductionCondition(BWAPI::UnitTypes::Terran_Factory,1)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Factory,ProductionEnums::Placement_MainBase,new SupplyCondition(18)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Machine_Shop,ProductionEnums::Placement_MainBase,new UnitProductionCondition(BWAPI::UnitTypes::Terran_Factory,2)));	
	twoFactVultures->AddItem(new UpgradeItem(BWAPI::UpgradeTypes::Ion_Thrusters,new UnitProductionCondition(BWAPI::UnitTypes::Terran_Machine_Shop,2)));	
	twoFactVultures->AddItem(new ResearchItem(BWAPI::TechTypes::Spider_Mines,new UnitProductionCondition(BWAPI::UnitTypes::Terran_Machine_Shop,2)));	
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Supply_Depot,ProductionEnums::Placement_MainBase,new SupplyCondition(23)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Supply_Depot,ProductionEnums::Placement_MainBase,new SupplyCondition(28)));
	_availableBuildOrders.push_back(twoFactVultures);
}
void BuildOrderHandler::SetCurrentBuildOrder()
{
	//Setting it to two fact vulture
	_currentBuildOrder = _availableBuildOrders.front();
}


void BuildOrderHandler::Update()
{
	if(initiated && !_currentBuildOrder->IsEmpty())
	{
		std::list<BuildOrderItem*> items = _currentBuildOrder->GetBuildOrderItems();
		for(std::list<BuildOrderItem*>::iterator item = items.begin();item!=items.end();++item)
		{
			bool allConditionsFulfilled = true;
			
			std::list<Condition*> conditions = (*item)->GetConditions();
			for each(Condition* condition in conditions)
			{
				if(!condition->IsFulfilled())
				{
					allConditionsFulfilled = false;
					break;
				}
			}
			//If all the conditions of the item was fulfilled we save it to the right list of tasks
			if(allConditionsFulfilled == true)
			{
				SaveAsTask(*item);				
				_currentBuildOrder->items.remove(*item);
			}
		}
	}
	else
	{
		InitiateBuildOrders();
		SetCurrentBuildOrder();
		initiated = true;
	}

}

void BuildOrderHandler::SaveAsTask(BuildOrderItem* item)
{
	if(item->GetType() == "UpgradeItem")
	{
		UpgradeItem* ui = dynamic_cast<UpgradeItem*>(item);
		upgradeTasks.push_back(new UpgradeTask(ui->upgradeType));
	}
	if(item->GetType() == "ResearchItem")
	{
		ResearchItem* ri = dynamic_cast<ResearchItem*>(item);
		researchTasks.push_back(new ResearchTask(ri->techType));
	}
	else if(item->GetType() == "BuildingItem")
	{
		BuildingItem* bi = dynamic_cast<BuildingItem*>(item);
		constructionTasks.push_back(new ConstructionTask(bi->building,bi->buildingPlacement));
	}
	else if(item->GetType() == "UnitProductionItem")
	{
		UnitProductionItem* ui = dynamic_cast<UnitProductionItem*>(item);
		unitProductionTasks.push_back(new UnitProductionTask(ui->unit,ui->number));
	}
	else if(item->GetType() == "ProductionFocusItem")
	{
		ProductionFocusItem* pi = dynamic_cast<ProductionFocusItem*>(item);
		productionFocusTasks.push_back(new ProductionFocusTask(pi->productionFocus));
	}
	else if(item->GetType() == "ScoutItem")
	{
		ScoutingManager::GetInstance()->Scout();
	}

}
void BuildOrderHandler::PrintBuildOrder(BuildOrder* buildorder)
{
	BWAPI::Broodwar->printf("Printing Build Order \n");
	std::list<BuildOrderItem*> items =  buildorder->GetBuildOrderItems();
	for each(BuildOrderItem* item in items)
	{
		BWAPI::Broodwar->printf("Buildorder item: %s \n",item->GetType().c_str());
	}
}