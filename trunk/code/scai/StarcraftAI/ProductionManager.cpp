#include "ProductionManager.h"
#include "ProductionTask.h"
#include "BuildOrderItem.h"
#include "BuildOrderHandler.h"
#include "WorkerManager.h"
#include "BuildingPlacer.h"
#include <algorithm>

//The production facilities owned
std::map<BWAPI::UnitType,std::list<BWAPI::Unit*>> productionFacilities;

//Tasks are saved to this list and handled if minerals and gas amounts are sufficient
std::list<ProductionTask*> _productionQueue;

//The current focus in production
ProductionEnums::ProductionFocus _productionFocus;

//Used for getting new tasks
BuildOrderHandler _buildOrderHandler;

ProductionManager::ProductionManager()
{

}


void ProductionManager::Update()
{
	//BWAPI::Broodwar->printf("Test");
	//BuildingPlacer bp;
	//bp.Construct(BWAPI::UnitTypes::Terran_Supply_Depot);
	
	std::list<ProductionTask*> tasks = _buildOrderHandler.GetProductionTasks();
	

	/*if(!tasks.empty())
	{
		//Adds the tasks from the buildorderhandler
		for each(ProductionTask* task in tasks)
		{
			if(task->GetType() != "ProductionFocusTask")
			{
				_productionQueue.push_back(task);
			}
			else
			{
				//No reason to wait to set this, because it costs nothing
				//_productionFocus = dynamic_cast<ProductionFocusTask*>(task)->focus;
			}
			
		}
	
		//Trying to produce the first item in the list
		ProductionTask* firstInLine = _productionQueue.front();

		//BWAPI::Broodwar->printf("Before GetTYpe");
		//BWAPI::Broodwar->printf("%s",firstInLine->GetType().c_str());
		//If we have enough mineral and gas then try doing the task
		if(firstInLine->mineralPrice <= BWAPI::Broodwar->self()->minerals() &&
			firstInLine->gasPrice <= BWAPI::Broodwar->self()->gas())
		{
			/*
			if("UnitProductionTask" == firstInLine->GetType())
			{
				BWAPI::Broodwar->printf("UnitProductionTast");
				TryProduceUnit(dynamic_cast<UnitProductionTask*>(firstInLine));
			}
			if("ConstructionTask" == firstInLine->GetType())
			{
				BWAPI::Broodwar->printf("ConstructionTast");
				TryConstructBuilding(dynamic_cast<ConstructionTask*>(firstInLine));
			}
			else if("ResearchTask" == firstInLine->GetType())
			{
				BWAPI::Broodwar->printf("ResearchTask");
				TryResearchTech(dynamic_cast<ResearchTask*>(firstInLine));
			}

		}
		
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
	*/
}

void ProductionManager::TryProduceUnit(UnitProductionTask* task)
{
	//Check if we have enough supply
	if((BWAPI::Broodwar->self()->supplyTotal()-BWAPI::Broodwar->self()->supplyUsed()) < task->unit.supplyRequired())
		return;

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
		RemoveTask(task);
	}
}
void ProductionManager::TryConstructBuilding(ConstructionTask* task)
{
	BWAPI::Broodwar->printf("trying to build");
	BuildingPlacer bp;
	bp.Construct(BWAPI::UnitTypes::Terran_Supply_Depot);
	/*
	BWAPI::TilePosition buildPosition;
	BWAPI::Unit* builder = WorkerManager::GetScv();
	//come up with a way to find a spot on the map to place building
	while(BWAPI::Broodwar->canBuildHere(builder,buildPosition,task.building,false)==false)
	{
		buildPosition = BWAPI::TilePosition(buildPosition.x()++,buildPosition.y()++);
	}
	builder->build(buildPosition,task.building);
	*/
}

void ProductionManager::TryResearchTech(ResearchTask* task)
{
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
void ProductionManager::RemoveTask(ProductionTask* task)
{
	
	for(std::list<ProductionTask*>::iterator pTask = _productionQueue.begin();pTask!=_productionQueue.end();pTask++)
	{
		
		if( *pTask == task)
		{
			_productionQueue.erase(pTask);
			break;
		}
	}
	
}
void ProductionManager::BuildingConstructed(BWAPI::Unit *building)
{
	productionFacilities[building->getType()].push_back(building);
}