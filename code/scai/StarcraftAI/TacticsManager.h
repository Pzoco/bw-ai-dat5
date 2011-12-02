#pragma once
#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>

class TacticsManager
{
public:
	TacticsManager(void);
	void Update();
	void AddSquad(Squad squad);
	void RemoveSquad(Squad squad);
	void AssignToSquad(BWAPI::Unit* unit);
	void AssignToSquads(std::set<BWAPI::Unit*> units);
	int static GetNumberOfUnits(BWAPI::UnitType type);
private:
	std::list<Squad> &GetRightSquadList(BWAPI::UnitType);
	void WriteSquadList(BWAPI::UnitType, std::list<Squad>);
};
