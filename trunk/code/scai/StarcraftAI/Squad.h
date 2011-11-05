#pragma once
#include "BaseTactic.h"
#include <BWAPI.h>
#include <BWTA.h>
class Squad
{
public:
	Squad(std::list<BWAPI::Unit*> units,BaseTactic tactic);
	Squad::Squad(BWAPI::Unit* unit,BaseTactic tactic);
	void ExecuteTactics();
	void AddUnit(BWAPI::Unit* unit);
	void RemoveUnit(BWAPI::Unit* unit);
};
