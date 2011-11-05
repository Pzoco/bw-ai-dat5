#pragma once
#include "Squad.h"
class TacticsManager
{
public:
	TacticsManager(void);
	void Update();
	void AddSquad(Squad squad);
	void RemoveSquad(Squad squad);
	void AssignToSquad(BWAPI::Unit* unit);
	void AssignToSquads(std::list<BWAPI::Unit*> units);
private:
	Squad GetRightSquadList(BWAPI::UnitType);
};
