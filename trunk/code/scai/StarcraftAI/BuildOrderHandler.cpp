#include "BuildOrderHandler.h"
#include "BuildOrder.h"
#include "Condition.h"
#include "BuildOrderItem.h"
#include "ResearchItem.h"
#include "BuildingItem.h"
#include "UnitProductionItem.h"
#include "ProductionFocusItem.h"
#include "ResearchItem.h"
#include "SupplyCondition.h"
#include "ProductionTask.h"



BuildOrderHandler::BuildOrderHandler(void)
{
	initiated =false;
}

void BuildOrderHandler::InitiateBuildOrders()
{
	BuildOrder* twoFactVultures =new BuildOrder();
	
	twoFactVultures->AddItem(new ProductionFocusItem(ProductionEnums::Focus_Workers,new SupplyCondition(4)));
	twoFactVultures->AddItem(new BuildingItem(BWAPI::UnitTypes::Terran_Supply_Depot,ProductionEnums::Placement_MainBase,new SupplyCondition(9)));
	//BWAPI::Broodwar->printf("%s",twoFactVultures->GetBuildOrderItems().front()->GetConditions().front()->IsFulfilled() ? "true" : "false");
	_availableBuildOrders.push_back(twoFactVultures);
}
void BuildOrderHandler::SetCurrentBuildOrder()
{
	//Setting it to two fact vulture
	_currentBuildOrder = _availableBuildOrders.front();
}

//Checks which build order items are ready for production (When all their conditions are fulfilled)
std::list<ProductionTask*> BuildOrderHandler::GetProductionTasks()
{
	std::list<ProductionTask*> productionTasks;
	if(initiated && !_currentBuildOrder->IsEmpty())
	{
		for each(BuildOrderItem* item in _currentBuildOrder->GetBuildOrderItems())
		{
			bool allConditionsFulfilled = true;
			for each(Condition* condition in item->GetConditions())
			{
				if(!condition->IsFulfilled())
				{
					allConditionsFulfilled = false;
					break;
				}
			}
			//If all the conditions of the item was fulfilled we save it to the list of productiontasks
			if(allConditionsFulfilled == true)
			{
				productionTasks.push_back(CreateProductionTask(item));
				
			}
		}
	}
	else
	{
		InitiateBuildOrders();
		SetCurrentBuildOrder();
		//PrintBuildOrder(_currentBuildOrder);
		BWAPI::Broodwar->printf("%d",_currentBuildOrder->GetBuildOrderItems().size());
		initiated = true;
	}
	return productionTasks;
}

ProductionTask* BuildOrderHandler::CreateProductionTask(BuildOrderItem* item)
{
	if(item->GetType() == "ResearchItem")
	{
		ResearchItem* ri = dynamic_cast<ResearchItem*>(item);
		return new ResearchTask(ri->techType);
	}
	else if(item->GetType() == "BuildingItem")
	{
		BuildingItem* bi = dynamic_cast<BuildingItem*>(item);
		return new ConstructionTask(bi->building,bi->buildingPlacement);
	}
	else if(item->GetType() == "UnitProductionItem")
	{
		UnitProductionItem* ui = dynamic_cast<UnitProductionItem*>(item);
		return new UnitProductionTask(ui->unit);
	}
	else if(item->GetType() == "ProductionFocusItem")
	{
		ProductionFocusItem* ui = dynamic_cast<ProductionFocusItem*>(item);
		return new ProductionFocusTask(ui->productionFocus);
	}
	return new ProductionTask();
}
void BuildOrderHandler::PrintBuildOrder(BuildOrder* buildorder)
{
	for each(BuildOrderItem* item in buildorder->GetBuildOrderItems())
	{
		BWAPI::Broodwar->printf("Buildorder item %s",item->GetType());
	}
}
void BuildOrderHandler::RemoveItem(BuildOrderItem* item)
{
	for(std::list<BuildOrderItem*>::iterator pItem = _currentBuildOrder->GetBuildOrderItems().begin();pItem!=_currentBuildOrder->GetBuildOrderItems().end();pItem++)
	{
		if( *pItem == item)
		{
			_currentBuildOrder->GetBuildOrderItems().erase(pItem);
			break;
		}
	}
}