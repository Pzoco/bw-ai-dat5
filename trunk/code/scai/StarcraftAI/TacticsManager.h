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
private:
	Squad GetRightSquadList(BWAPI::UnitType);
};
