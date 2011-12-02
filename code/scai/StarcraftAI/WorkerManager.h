#pragma once
#include <BWAPI.h>

class WorkerManager
{
public:
	enum ScvState{Constructing,BeingBuild,MiningGas,MiningMinerals,Defending,Evading,Nothing};
	WorkerManager(void);
	void ScvCreated(BWAPI::Unit* scv);
	void InitiateStartingMinerals();
	void Update();
	BWAPI::Unit* GetScvNearPosition(BWAPI::Position position);
	static BWAPI::Unit* GetScv();
};
