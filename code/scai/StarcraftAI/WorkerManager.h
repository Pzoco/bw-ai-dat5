#pragma once
#include <BWAPI.h>

class WorkerManager
{
public:
	enum ScvState{Constructing,BeingBuild,MiningGas,MiningMinerals,Defending,Evading,Nothing};
	WorkerManager(void);
	void AddMineralLine(std::set<BWAPI::Unit*> minerals);
	void AddRefinery(BWAPI::Unit* refinery);
	void ScvCreated(BWAPI::Unit* scv);
	void ScvKilled(BWAPI::Unit* scv);
	void SendToMineral(BWAPI::Unit* scv);
	void SendToGas(BWAPI::Unit* scv);
	void Update();
	BWAPI::Unit* GetScvNearPosition(BWAPI::Position position);
	static BWAPI::Unit* GetScv();
private:
	void InitiateStartingMinerals();
};
