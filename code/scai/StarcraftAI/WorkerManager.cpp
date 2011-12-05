#include "WorkerManager.h"
#include <BWAPI.h>


//Used to find the best mineral or refinery
std::map<BWAPI::Unit*,int> _workersOnRefinery;
std::map<BWAPI::Unit*,int> _workersOnMineral;

//Workers owned
std::list<BWAPI::Unit*> _scvs;
//Scv mapped to a resource
std::map<BWAPI::Unit*,BWAPI::Unit*> _scvResourceGoals;
std::map<BWAPI::Unit*,WorkerManager::ScvState> _scvStates;

bool isInitiated = false;

WorkerManager::WorkerManager(void)
{

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
	BWAPI::Unit* goal = _scvResourceGoals[scv];
	if(_scvStates[scv] == WorkerManager::MiningGas)
	{
		_workersOnRefinery[scv]--;
	}
	else if(_scvStates[scv] == WorkerManager::MiningMinerals)
	{
		_workersOnMineral[scv]--;
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
					_scvStates[scv] = WorkerManager::Nothing;
				}
			}
			else if(_scvStates[scv] == WorkerManager::Nothing)
			{
				_scvStates[scv] = WorkerManager::MiningMinerals;
				SendToMineral(scv);
			}
		}

		//Checks if there is a refinery that is not being mined
		//Could be improved if time
		for(std::map<BWAPI::Unit*,int>::iterator r = _workersOnRefinery.begin();r!=_workersOnRefinery.end();r++)
		{
			if(r->second == 0 && r->first->isCompleted())
			{
				for(int i = 0;i<3;i++)
				{
					SendToGas(GetScvNearPosition(r->first->getPosition()));
				}
			}
		}
	}
	else
	{
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