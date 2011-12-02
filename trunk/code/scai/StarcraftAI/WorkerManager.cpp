#include "WorkerManager.h"
#include <BWAPI.h>


//Used to find the best mineral or refinery
std::map<BWAPI::Unit*,int> _workersOnRefinery;
std::map<BWAPI::Unit*,int> _workersOnMineral;

//Workers owned
std::list<BWAPI::Unit*> _scvs;
std::map<BWAPI::Unit*,BWAPI::Unit*> _scvResourceGoals;
std::map<BWAPI::Unit*,WorkerManager::ScvState> _scvStates;

bool isInitiated = false;

WorkerManager::WorkerManager(void)
{

}
void WorkerManager::ScvCreated(BWAPI::Unit* scv)
{
	_scvs.push_back(scv);
	
	//Used for finding the best patch
	int fewestScvs = 100;
	BWAPI::Unit* bestMineral;
	if(!isInitiated)
		InitiateStartingMinerals();

	//Finds the best mineral patch by looking at number of workers per patch
	for(std::map<BWAPI::Unit*,int>::iterator m = _workersOnMineral.begin();m != _workersOnMineral.end();m++)
	{
		if((*m).second < fewestScvs)
		{
			fewestScvs = (*m).second;
			bestMineral = (*m).first;
		}
	}
	//Sets the mineral patch to contain one more worker
	_workersOnMineral[bestMineral]++;
	_scvResourceGoals[scv]=bestMineral;
	_scvStates[scv] = WorkerManager::BeingBuild;
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
void WorkerManager::Update()
{
	if(isInitiated)
	{
		for each(BWAPI::Unit* scv in _scvs)
		{
			if(_scvStates[scv] == WorkerManager::BeingBuild)
			{
				if(scv->isCompleted())
				{
					_scvStates[scv] = WorkerManager::Nothing;
				}
			}
			else if(_scvStates[scv] == WorkerManager::Nothing)
			{
				_scvStates[scv] = WorkerManager::MiningMinerals;
				scv->rightClick(_scvResourceGoals[scv]);
			}
		}
	}
}
BWAPI::Unit* WorkerManager::GetScvNearPosition(BWAPI::Position position)
{
	int closestDistance = 100000;
	BWAPI::Unit* closestScv;
	for each(BWAPI::Unit* scv in _scvs)
	{
		int distance = scv->getDistance(position);
		if(closestDistance > distance)
		{
			closestDistance = distance;
			closestScv = scv;
		}
	}
	return closestScv;
}
BWAPI::Unit* WorkerManager::GetScv()
{
	return _scvs.front();
}