#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>
#include "BaseTactic.h"

std::set<BWAPI::Unit*> _units;
BWAPI::UnitType _unitType;
BaseTactic _tactic;

Squad::Squad()
{

}
Squad::Squad(std::set<BWAPI::Unit*> units,BaseTactic tactic)
{
	_units = units;
	_tactic = tactic;
	_unitType = (*_units.begin())->getType();
}
Squad::Squad(BWAPI::Unit* unit,BaseTactic tactic)
{
	_units.insert(unit);
	_tactic = tactic;
	_unitType = (*_units.begin())->getType();
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
		if((*u)->exists())
		{
			_tactic.ExecuteTactic((*u),_units);
		}
	}
}
int Squad::GetSize()
{
	return _units.size();
}
BWAPI::UnitType Squad::GetUnitType()
{
	return _unitType;
}
BWAPI::Position Squad::GetSquadCenter()
{
	int mass = 1;
	int n = 0;
	int x = 0;
	int y = 0;
	for(std::set<BWAPI::Unit*>::const_iterator i = _units.begin(); i != _units.end(); i++)
	{
		if((*i)->exists())
		{
			n++;
			BWAPI::Position unitPos = (*i)->getPosition();
			x += (mass*unitPos.x());
		}
	}
	x = x/(n*mass);

	for(std::set<BWAPI::Unit*>::const_iterator j = _units.begin(); j != _units.end(); j++)
	{
		if((*j)->exists())
		{
			BWAPI::Position unitPos = (*j)->getPosition();
			y += (mass*unitPos.y());
		}
	}
	y = y/(n*mass);

	//Center is now calculated
	
	return BWAPI::Position(x,y);

}