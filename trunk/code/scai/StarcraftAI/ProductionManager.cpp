#include "ProductionManager.h"
#include "ProductionTask.h"
#include "BuildOrderItem.h"
#include "BuildOrderHandler.h"
#include "WorkerManager.h"
#include "BuildingPlacementFinder.h"
#include "UnitHelper.h"
#include <algorithm>




//The production facilities owned
std::map<BWAPI::UnitType,std::list<BWAPI::Unit*>> productionFacilities;

//Research/Upgrade facilities owned
std::map<BWAPI::UnitType,std::list<BWAPI::Unit*>> researchFacilities;

//The current focus in production
ProductionEnums::ProductionFocus _productionFocus;

//Used for getting new tasks
BuildOrderHandler _buildOrderHandler;

//BuildingPlacementFinder
BuildingPlacementFinder _buildingPlacer;

ProductionManager* ProductionManager::productionManager=0;

ProductionManager::ProductionManager(){}
ProductionManager* ProductionManager::GetInstance()
{
	if(productionManager==NULL)
	{
		productionManager=new ProductionManager;
	}
	return productionManager;
}
void ProductionManager::BuildingConstructed(BWAPI::Unit *building)
{
	if(building->getType().canProduce())
	{
		productionFacilities[building->getType()].push_back(building);
	}
	else
	{
		researchFacilities[building->getType()].push_back(building);
	}
}
void ProductionManager::BuildingDestroyed(BWAPI::Unit *building)
{
	for each(BWAPI::Unit* b in productionFacilities[building->getType()])
	{
		if(b == building)
		{
			productionFacilities[building->getType()].remove(b);
			break;
		}
	}
}
void ProductionManager::Update()
{
	_buildOrderHandler.Update();
	RetrieveTasks();
	
	//Here we check if there are any tasks ready
	if(!_productionFocusTasks.empty())
	{
		_productionFocus = _productionFocusTasks.front()->focus;
		_productionFocusTasks.erase(_productionFocusTasks.begin());
	}
	if(!_constructionTasks.empty())
	{
		ConstructionTask* firstInLine = _constructionTasks.front();
		bool success = TryConstructBuilding(firstInLine);
		if(success)
			_constructionTasks.erase(_constructionTasks.begin());
	}
	if(!_unitProductionTasks.empty())
	{
		bool success = TryProduceUnit(_unitProductionTasks.front());
		if(success)
			_unitProductionTasks.erase(_unitProductionTasks.begin());
	}
	if(!_upgradeTasks.empty())
	{
		bool success = TryUpgradeTech(_upgradeTasks.front());
		if(success)
			_upgradeTasks.erase(_upgradeTasks.begin());
	}
	if(!_researchTasks.empty())
	{
		bool success = TryResearchTech(_researchTasks.front());
		if(success)
			_researchTasks.erase(_researchTasks.begin());
	}
	
	//Build scvs if this is the focus right now
	if(_productionFocus == ProductionEnums::Focus_Workers)
	{
		for each(BWAPI::Unit* cc in productionFacilities[BWAPI::UnitTypes::Terran_Command_Center])
		{
			if(!cc->isTraining())
			{
				cc->train(BWAPI::UnitTypes::Terran_SCV);
			}
		}
	}
}

void ProductionManager::RetrieveTasks()
{
	//Gets all the newest tasks from the buildorderhandler
	_constructionTasks.merge(_buildOrderHandler.GetConstructionTasks());
	_researchTasks.merge(_buildOrderHandler.GetResearchTasks());
	_upgradeTasks.merge(_buildOrderHandler.GetUpgradeTasks());
	_unitProductionTasks.merge(_buildOrderHandler.GetUnitProductionTasks());
	_productionFocusTasks.merge(_buildOrderHandler.GetProductionFocusTasks());
}
bool ProductionManager::TryProduceUnit(UnitProductionTask* task)
{
	//Check if we have enough supply
	if((BWAPI::Broodwar->self()->supplyTotal()-BWAPI::Broodwar->self()->supplyUsed()) < task->unit.supplyRequired())
		return false;

	//Check if we got the money
	if(task->unit.mineralPrice() > BWAPI::Broodwar->self()->minerals() &&
		task->unit.gasPrice() > BWAPI::Broodwar->self()->gas())
	{
		return false;
	}

	bool allBuildingsFound = true;
	//If we have the required buildings and they are not currently producing, then build the unit
	for(std::map<BWAPI::UnitType,int>::iterator i = task->requiredBuildings.begin();i!=task->requiredBuildings.end();i++)
	{
		if(productionFacilities[i->first].empty())
		{
			allBuildingsFound = false;
			break;
		}
	}

	//Trying to find a production facility that is capable of producing the unit
	bool suitableProductionFacilityFound = false;
	BWAPI::Unit* suitableBuilding;
	for each(BWAPI::Unit* building in productionFacilities[task->unit.whatBuilds().first])
	{
		if(building->isIdle())
		{
			suitableBuilding = building;
			suitableProductionFacilityFound = true;
			break;
		}
	}
	if(allBuildingsFound && suitableProductionFacilityFound)
	{
		task->number--;
		suitableBuilding->train(task->unit);
		if(task->number == 0)
		{
			return true;
		}
		return false;
	}
	return false;
}
bool ProductionManager::TryConstructBuilding(ConstructionTask* task)
{
	//BWAPI::Broodwar->printf("Trying to build %s",task->building.getName().c_str());
	if(task->building.mineralPrice()<=BWAPI::Broodwar->self()->minerals() &&
		task->building.gasPrice()<=BWAPI::Broodwar->self()->gas())
	{
		if(task->building.isAddon())
		{
			//BWAPI::Broodwar->printf("We need a %s",UnitHelper::GetMainBuildingOfAddon(task->building).getName().c_str());
			for each(BWAPI::Unit* p in productionFacilities[UnitHelper::GetMainBuildingOfAddon(task->building)])
			{
				if(p->canIssueCommand(BWAPI::UnitCommand::buildAddon(p,task->building)))
				{
					//BWAPI::Broodwar->printf("Trying to build addon");
					p->buildAddon(task->building);
					if(p->getAddon() == NULL)
					{
						return false;
					}
					return true;	
				}
			}
		}
		else
		{
			WorkerManager::GetInstance()->ConstructBuilding(task->building,task->placement);
			return true;
		}
	}
	return false;
}

bool ProductionManager::TryUpgradeTech(UpgradeTask* task)
{
	//If we dont have the money it fails
	if(task->techType.mineralPrice() > BWAPI::Broodwar->self()->minerals() ||
		task->techType.gasPrice() > BWAPI::Broodwar->self()->gas())
	{
		return false;
	}

	//If it cant find a suitable building it fails
	bool suitableResearchFacilityFound = false;
	BWAPI::Unit* suitableBuilding;
	
	for each(BWAPI::Unit* building in researchFacilities[task->techType.whatUpgrades()])
	{
		if(building == NULL)
			break;
		if(building->isIdle())
		{
			suitableBuilding = building;
			suitableResearchFacilityFound=true;
			break;
		}
	}
	if(suitableResearchFacilityFound)
	{
		return suitableBuilding->upgrade(task->techType);
	}
	return false;
}


bool ProductionManager::TryResearchTech(ResearchTask* task)
{
	//If we dont have the money it fails
	if(task->techType.mineralPrice() > BWAPI::Broodwar->self()->minerals() ||
		task->techType.gasPrice() > BWAPI::Broodwar->self()->gas())
	{
		return false;
	}

	//If it cant find a suitable building it fails
	bool suitableResearchFacilityFound = false;
	BWAPI::Unit* suitableBuilding;
	
	for each(BWAPI::Unit* building in researchFacilities[task->techType.whatResearches()])
	{
		if(building == NULL)
			break;
		if(building->isIdle())
		{
			suitableBuilding = building;
			suitableResearchFacilityFound=true;
			break;
		}
	}
	if(suitableResearchFacilityFound)
	{
		return suitableBuilding->research(task->techType);
	}
	return false;
}

