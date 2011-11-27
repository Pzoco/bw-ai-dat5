#include "ProductionManager.h"
#include "BuildingPlacer.h"
#include "BuildOrder.h"

BuildingPlacer _buildingPlacer;
BuildOrder _currentBuildOrder;
std::list<BuildOrder> _allBuildOrders;
std::list<BWAPI::Unit*> _scvs;
BuildOrderItem::ProductionFocus _productionFocus;

ProductionManager::ProductionManager()
{
	InitiateBuildOrders();
	//Always 2 fact vulture now
	SetCurrentBuildOrder();

}

void ProductionManager::AssignScv(BWAPI::Unit* unit)
{
	_scvs.push_back(unit);
}
void ProductionManager::AssignScvs(std::set<BWAPI::Unit*> units)
{
	for each(BWAPI::Unit* unit in units)
	{
		if(unit->getType() == BWAPI::UnitTypes::Terran_SCV)
		{
			_scvs.push_back(unit);
		}
	}
}
void ProductionManager::InitiateBuildOrders()
{
	BuildOrder twoFactVultures = BuildOrder();
	
	//Enum stuff doesnt look good - Might need a fix later
	twoFactVultures.AddItem(ProductionFocusItem(BuildOrderItem::Focus_Workers,SupplyCondition(4)));
	twoFactVultures.AddItem(BuildingItem(BWAPI::UnitTypes::Terran_Supply_Depot,SupplyCondition(9)));
	_allBuildOrders.push_back(twoFactVultures);
}
void ProductionManager::SetCurrentBuildOrder()
{
	_currentBuildOrder = _allBuildOrders.front();
}
void ProductionManager::Update()
{
	for each(BuildOrderItem item in _currentBuildOrder.GetBuildOrderItems())
	{
		bool allConditionsFulfilled = true;
		for each(Condition condition in item.GetConditions())
		{
			if(!condition.IsFulfilled())
			{
				allConditionsFulfilled = false;
				break;
			}
		}
		if(allConditionsFulfilled == true)
		{
			switch(item.GetType())
			{
				case 1: ResearchTech(dynamic_cast<ResearchItem&>(item).techType); break;
				case 2: ConstructBuilding(dynamic_cast<BuildingItem&>(item).building); break;
				case 3: ProduceUnit(dynamic_cast<UnitProductionItem&>(item).unit); break;
				case 4: _productionFocus = dynamic_cast<ProductionFocusItem&>(item).productionFocus;
			}

		}
	}
}

void ProductionManager::ProduceUnit(BWAPI::UnitType unitType)
{
	
}
void ProductionManager::ConstructBuilding(BWAPI::UnitType buildingType)
{

}

void ProductionManager::ResearchTech(BWAPI::TechType techType)
{

}