#include "ProductionManager.h"
#include "ProductionTask.h"
#include "BuildOrderItem.h"
#include "BuildOrderHandler.h"
#include "WorkerManager.h"
#include "BuildingPlacer.h"
#include <algorithm>

//The production facilities owned
std::map<BWAPI::UnitType,std::list<BWAPI::Unit*>> productionFacilities;

//The current focus in production
ProductionEnums::ProductionFocus _productionFocus;

//Used for getting new tasks
BuildOrderHandler _buildOrderHandler;

//BuildingPlacer
BuildingPlacer _buildingPlacer;

ProductionManager::ProductionManager()
{

}


void ProductionManager::BuildingConstructed(BWAPI::Unit *building)
{
	productionFacilities[building->getType()].push_back(building);
}
void ProductionManager::Update()
{
	_buildOrderHandler.Update();
	RetrieveTasks();
	
	//Here we check if there are any tasks ready
	if(!_productionFocusTasks.empty())
	{
		_productionFocus = _productionFocusTasks.front()->focus;
		_productionFocusTasks.remove(_productionFocusTasks.front());
	}
	if(!_constructionTasks.empty())
	{
		ConstructionTask* firstInLine = _constructionTasks.front();
		TryConstructBuilding(firstInLine);
	}
	if(!_unitProductionTasks.empty())
	{
		UnitProductionTask* firstInLine = _unitProductionTasks.front();
		TryProduceUnit(firstInLine);
	}
	if(!_researchTasks.empty())
	{
		ResearchTask* firstInLine = _researchTasks.front();
		TryResearchTech(firstInLine);
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
	_unitProductionTasks.merge(_buildOrderHandler.GetUnitProductionTasks());
	_productionFocusTasks.merge(_buildOrderHandler.GetProductionFocusTasks());
}
void ProductionManager::TryProduceUnit(UnitProductionTask* task)
{
	//Check if we have enough supply
	if((BWAPI::Broodwar->self()->supplyTotal()-BWAPI::Broodwar->self()->supplyUsed()) < task->unit.supplyRequired())
		return;
	
	//Check if we got the money
	if(task->unit.mineralPrice() > BWAPI::Broodwar->self()->minerals() &&
		task->unit.gasPrice() > BWAPI::Broodwar->self()->gas())
	{
		return;
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
	for each(BWAPI::Unit* building in productionFacilities[task->unit])
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
		suitableBuilding->train(task->unit);
		//RemoveTask(task);
	}
}
void ProductionManager::TryConstructBuilding(ConstructionTask* task)
{
	//Check if we got the money
	if(task->building.mineralPrice() > BWAPI::Broodwar->self()->minerals() ||
		task->building.gasPrice() > BWAPI::Broodwar->self()->gas())
	{
		return;
	}
	_buildingPlacer.Construct(task->building);
}

void ProductionManager::TryResearchTech(ResearchTask* task)
{
	if(task->techType.mineralPrice() > BWAPI::Broodwar->self()->minerals() ||
		task->techType.gasPrice() > BWAPI::Broodwar->self()->gas())
	{
		return;
	}

	bool suitableResearchFacilityFound = false;
	BWAPI::Unit* suitableBuilding;
	for each(BWAPI::Unit* building in productionFacilities[task->techType.whatResearches()])
	{
		if(building->isIdle())
		{
			suitableBuilding = building;
			suitableResearchFacilityFound=true;
			break;
		}
	}
	if(suitableResearchFacilityFound)
	{
		suitableBuilding->research(task->techType);
	}
}
