#pragma once
#include <BWAPI.h>
#include "ProductionEnums.h"
#include "BuildingPlacementFinder.h"

typedef std::map<BWAPI::TilePosition,BWAPI::UnitType> buildingToConstruct;
class WorkerManager
{
public:
	enum ScvState{Constructing,BeingBuild,MiningGas,MiningMinerals,Defending,Evading,Nothing};
	static WorkerManager* GetInstance();
	void AddMineralLine(std::set<BWAPI::Unit*> minerals);
	void AddRefinery(BWAPI::Unit* refinery);
	void ScvCreated(BWAPI::Unit* scv);
	void ScvKilled(BWAPI::Unit* scv);
	void Update();
	void ConstructBuilding(BWAPI::UnitType buildingType,ProductionEnums::BuildingPlacement placement);
private:
	BWAPI::Unit* _newRefinery;
	std::list<BWAPI::Unit*> _scvs;
	std::map<BWAPI::Unit*,int> _workersOnRefinery;
	std::map<BWAPI::Unit*,int> _workersOnMineral;
	std::map<BWAPI::Unit*,buildingToConstruct> _workersOnConstruction;
	std::map<BWAPI::Unit*,BWAPI::Unit*> _buildingsUnderConstruction;
	std::map<BWAPI::Unit*,BWAPI::Unit*> _scvResourceGoals;
	std::map<BWAPI::Unit*,WorkerManager::ScvState> _scvStates;
	WorkerManager();
	static WorkerManager* workerManager;
	void InitiateStartingMinerals();
	void SwitchState(BWAPI::Unit* scv,ScvState newState);
	void SendToMineral(BWAPI::Unit* scv);
	void SendToGas(BWAPI::Unit* scv);
	BWAPI::Unit* GetScvNearPosition(BWAPI::Position position);
	BWAPI::Unit* GetAvailableScvNearPosition(BWAPI::Position position);
};