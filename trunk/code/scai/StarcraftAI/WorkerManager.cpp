#include "WorkerManager.h"
#include "ProductionManager.h"
#include <BWAPI.h>


WorkerManager* WorkerManager::workerManager=0;
bool isInitiated = false;
BuildingPlacementFinder finder;

WorkerManager::WorkerManager(){}
WorkerManager* WorkerManager::GetInstance()
{
	if(workerManager==NULL)
	{
		workerManager= new WorkerManager();
	}
	return workerManager;
}
void WorkerManager::AddMineralLine(std::set<BWAPI::Unit*> minerals)
{
	for(std::set<BWAPI::Unit*>::iterator m=minerals.begin();m!=minerals.end();m++)
	{
		//There is currently no workers on this patch
		_workersOnMineral[(*m)] = 0;
	}
}
void WorkerManager::AddRefinery(BWAPI::Unit* refinery)
{
	_workersOnRefinery[refinery]=0;
	_newRefinery = refinery;
}
void WorkerManager::ScvCreated(BWAPI::Unit* scv)
{
	_scvs.push_back(scv);
	if(scv->isCompleted())
	{
		_scvStates[scv] = WorkerManager::Nothing;
	}
	else
	{
		_scvStates[scv] = WorkerManager::BeingBuild;
	}
}

void WorkerManager::ScvKilled(BWAPI::Unit* scv)
{
	if(_scvStates[scv] == WorkerManager::MiningGas)
	{
		_workersOnRefinery[scv]--;
		_scvResourceGoals.erase(_scvResourceGoals.find(scv));
	}
	else if(_scvStates[scv] == WorkerManager::MiningMinerals)
	{
		_workersOnMineral[scv]--;
		_scvResourceGoals.erase(_scvResourceGoals.find(scv));
	}
	_scvs.remove(scv);
}
void WorkerManager::SendToMineral(BWAPI::Unit* scv)
{
	//Used for finding the best patch
	int fewestScvs = 100;
	int distanceToMineral = 10000;
	BWAPI::Unit* bestMineral;

	//Finds the best mineral patch by looking at number of workers per patch
	for(std::map<BWAPI::Unit*,int>::iterator m = _workersOnMineral.begin();m != _workersOnMineral.end();m++)
	{
		if((*m).second < fewestScvs)
		{
			fewestScvs = (*m).second;
			bestMineral = (*m).first;
			distanceToMineral=scv->getDistance(bestMineral);
		}
		else if((*m).second ==fewestScvs && scv->getDistance((*m).first)<distanceToMineral)
		{
			fewestScvs = (*m).second;
			bestMineral = (*m).first;
			distanceToMineral=scv->getDistance(bestMineral);
		}
	}
	//Sets the mineral patch to contain one more worker
	_workersOnMineral[bestMineral]++;
	_scvResourceGoals[scv]=bestMineral;
	//BWAPI::Broodwar->printf("Sending a scv to %d,%d",bestMineral->getPosition().x(),bestMineral->getPosition().y());
	scv->rightClick(bestMineral);
}
void WorkerManager::SendToGas(BWAPI::Unit* scv)
{
	//Used for finding the best patch
	int fewestScvs = 100;
	int distanceToGas = 10000;
	BWAPI::Unit* bestGas;
	
	//Finds the best refinery by looking at number of workers per refinery
	for(std::map<BWAPI::Unit*,int>::iterator g = _workersOnRefinery.begin();g != _workersOnRefinery.end();g++)
	{
		if((*g).second < fewestScvs)
		{
			fewestScvs = (*g).second;
			bestGas = (*g).first;
			distanceToGas = scv->getDistance(bestGas);
		}
		else if((*g).second == fewestScvs && scv->getDistance((*g).first)<distanceToGas)
		{
			fewestScvs = (*g).second;
			bestGas = (*g).first;
			distanceToGas=scv->getDistance(bestGas);
		}
	}

	//Sets the worker to mine gas
	_workersOnMineral[bestGas]++;
	_scvResourceGoals[scv]=bestGas;
	scv->rightClick(bestGas);
}
void WorkerManager::InitiateStartingMinerals()
{
	if(!isInitiated)
	{
		//Save the minerals in base
		for(std::set<BWAPI::Unit*>::iterator m=BWAPI::Broodwar->getMinerals().begin();m!=BWAPI::Broodwar->getMinerals().end();m++)
		{
			if((*m)->isVisible())
			{
				//There is currently no workers on this patch
				_workersOnMineral[(*m)] = 0;
			}
		}
		isInitiated = true;
	}
}
void WorkerManager::ConstructBuilding(BWAPI::UnitType buildingType,ProductionEnums::BuildingPlacement placement)
{

	BWAPI::TilePosition position = finder.FindBuildLocation(buildingType,placement);

	//Get a scv near the building position
	BWAPI::Unit* scv = GetAvailableScvNearPosition(BWAPI::Position(position.x(),position.y()));
	
	//Switch the state of the scv
	SwitchState(scv,WorkerManager::Constructing);
	
	//Mapping the scv to this building
	buildingToConstruct building;	
	building[position] = buildingType;
	_workersOnConstruction[scv] = building;

	//Sets it to build the building
	BWAPI::Broodwar->printf("Tries to build %s at %d , %d",buildingType.getName().c_str(),position.x(),position.y());
	scv->build(position,buildingType);
}
void WorkerManager::Update()
{
	if(isInitiated)
	{
		//Checks what the scvs are doing
		for each(BWAPI::Unit* scv in _scvs)
		{
			if(_scvStates[scv] == WorkerManager::BeingBuild)
			{
				if(scv->isCompleted())
				{
					SwitchState(scv,WorkerManager::Nothing);
				}
			}
			else if(_scvStates[scv] == WorkerManager::Nothing)
			{
				SwitchState(scv,WorkerManager::MiningMinerals);
				SendToMineral(scv);
			}
			else if(_scvStates[scv] == WorkerManager::Constructing)
			{
				if(scv->isConstructing())
				{
					if(_buildingsUnderConstruction[scv] == NULL)
						_buildingsUnderConstruction[scv] = scv->getBuildUnit();
				}
				else
				{
					if(_buildingsUnderConstruction[scv] == NULL)
					{
						//Gets the position and type to construct (Gets the first item, because there is only one)
						buildingToConstruct b = _workersOnConstruction[scv];
						buildingToConstruct::iterator i = b.begin();
						//BWAPI::Broodwar->printf("Tries to build %s at %d,%d",(*i).second.getName().c_str(),(*i).first.x(),(*i).first.y());
						scv->build((*i).first,(*i).second);
					}
					else if(_buildingsUnderConstruction[scv]->isCompleted())
					{
						//If the building is done then set the scv to do something else
						if(_buildingsUnderConstruction[scv]->getType() == BWAPI::UnitTypes::Terran_Refinery)
							AddRefinery(_buildingsUnderConstruction[scv]);
						_buildingsUnderConstruction[scv] = NULL;
						SwitchState(scv,WorkerManager::Nothing);
					}
				}
			}
		}

		
		//Sends scvs to new gas
		if(_newRefinery != NULL)
		{
			 for(int i =0;i<3;i++)
			 {
				 BWAPI::Unit* scv = GetAvailableScvNearPosition(_newRefinery->getPosition());
				 if(scv == NULL)
				 {
					 scv = GetScvNearPosition(_newRefinery->getPosition());
				 }
				 SwitchState(scv,WorkerManager::MiningGas);
				 SendToGas(scv);
			 }
			 _newRefinery = NULL;
		}
	}
	else
	{
		_newRefinery = NULL;
		InitiateStartingMinerals();
	}
}
BWAPI::Unit* WorkerManager::GetScvNearPosition(BWAPI::Position position)
{
	int closestDistance = 100000;
	BWAPI::Unit* closestScv;
	for each(BWAPI::Unit* scv in _scvs)
	{
		int distance = scv->getDistance(position);
		if(closestDistance > distance && scv->isCompleted())
		{
			closestDistance = distance;
			closestScv = scv;
		}
	}
	return closestScv;
}
BWAPI::Unit* WorkerManager::GetAvailableScvNearPosition(BWAPI::Position position)
{
	int closestDistance = 100000;
	BWAPI::Unit* closestScv;
	for each(BWAPI::Unit* scv in _scvs)
	{
		int distance = scv->getDistance(position);
		if(closestDistance > distance && !(scv->isCarryingGas() || scv->isCarryingMinerals() || !scv->isCompleted())
			&& _scvStates[scv] != WorkerManager::Constructing && _scvStates[scv] != WorkerManager::MiningGas &&_scvStates[scv] != WorkerManager::Scouting)
		{
			closestDistance = distance;
			closestScv = scv;
		}
	}
	return closestScv;
}
void WorkerManager::SwitchState(BWAPI::Unit* scv,ScvState newState)
{
	if(_scvStates[scv] == WorkerManager::MiningGas)
	{
		_workersOnRefinery[_scvResourceGoals[scv]]--;
	}
	else if(_scvStates[scv] == WorkerManager::MiningMinerals)
	{
		_workersOnMineral[_scvResourceGoals[scv]]--;
	}
	else if(_scvStates[scv] == WorkerManager::Constructing)
	{
		_workersOnConstruction[scv].clear();
	}
	_scvStates[scv] = newState;
}

BWAPI::Unit* WorkerManager::RequestSCV()
{
	Unit* scv=GetAvailableScvNearPosition(BWAPI::Position(BWAPI::TilePosition(BWAPI::Broodwar->self()->getStartLocation())));
	SwitchState(scv,WorkerManager::Scouting);
	return scv;
}

void WorkerManager::ReturnSCV(BWAPI::Unit* unit)
{
	_scvStates[unit]=WorkerManager::Nothing;
}