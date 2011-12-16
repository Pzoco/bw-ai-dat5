#pragma once
#include "BaseTactic.h"
#include <BWAPI.h>
#include <BWTA.h>
class Squad
{
public:
	Squad();
	Squad(std::set<BWAPI::Unit*> units,BaseTactic tactic);
	Squad::Squad(BWAPI::Unit* unit,BaseTactic tactic);
	void ExecuteTactics();
	void AddUnit(BWAPI::Unit* unit);
	void RemoveUnit(BWAPI::Unit* unit);
	int GetSize();
	BWAPI::Position GetSquadCenter();
	BWAPI::UnitType GetUnitType();
	BWAPI::Position LocationToMoveTo;
};
