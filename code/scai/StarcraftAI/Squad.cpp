#include "Squad.h"
#include "BaseTactic.h"
#include <BWAPI.h>
#include <BWTA.h>


std::list<BWAPI::Unit*> _units;
BaseTactic _tactic;

Squad::Squad(std::list<BWAPI::Unit*> units,BaseTactic tactic)
{
	_units = units;
	_tactic = tactic;
}
Squad::Squad(BWAPI::Unit* unit,BaseTactic tactic)
{
	_units.push_back(unit);
	_tactic = tactic;
}
void Squad::ExecuteTactics()
{
	for each(BWAPI::Unit* unit in _units)
	{
		_tactic.ExecuteTactic(unit);
	}
}



void Squad::AddUnit(BWAPI::Unit* unit)
{
	
}