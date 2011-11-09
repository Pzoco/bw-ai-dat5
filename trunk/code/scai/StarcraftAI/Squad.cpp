#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>
#include "BaseTactic.h"

std::set<BWAPI::Unit*> _units;
BaseTactic _tactic;

Squad::Squad()
{

}
Squad::Squad(std::set<BWAPI::Unit*> units,BaseTactic tactic)
{
	_units = units;
	_tactic = tactic;
}
Squad::Squad(BWAPI::Unit* unit,BaseTactic tactic)
{
	_units.insert(unit);
	_tactic = tactic;
}
void Squad::AddUnit(BWAPI::Unit* unit)
{
	_units.insert(unit);
}
void Squad::RemoveUnit(BWAPI::Unit* unit)
{
	for(std::set<BWAPI::Unit*>::const_iterator u = _units.begin(); u != _units.end(); u++)
	{
		if(unit == (*u))
		{
			_units.erase(u);
		}
	}
}
void Squad::ExecuteTactics()
{
	for(std::set<BWAPI::Unit*>::iterator u = _units.begin(); u != _units.end(); u++)
	{
		_tactic.ExecuteTactic((*u),_units);
	}
}
int Squad::GetSize()
{
	return _units.size();
}