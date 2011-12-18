#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>
#include "BaseTactic.h"
#include "MathHelper.h"
#include "TacticsManager.h"

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
	int numberOfUnits = 0;
	for(std::set<BWAPI::Unit*>::const_iterator u = _units.begin(); u != _units.end(); u++)
	{
		if((*u)->exists())
		{
			numberOfUnits++;
		}
	}

	BWAPI::Position LocationToMoveTo = TacticsManager::GetInstance()->attackPos;


	if(BWAPI::Broodwar->getFrameCount() % 200 == 0)
	{
			BWAPI::Broodwar->printf("target %d , %d",LocationToMoveTo.x(),LocationToMoveTo.y());
				
	}
	int minimumDistToEnemies = 100000;	
	for(std::set<BWAPI::Unit*>::iterator v = _units.begin(); v != _units.end(); v++)
	{	
		if((*v)->exists())
		{
			int distToEnemies = MathHelper::GetDistanceToNearestEnemy((*v)->getPosition());
			if(distToEnemies < minimumDistToEnemies)
			{
				minimumDistToEnemies = distToEnemies;
			}
		}
	}
	for(std::set<BWAPI::Unit*>::iterator u = _units.begin(); u != _units.end(); u++)
	{
		
		if((*u)->exists() && minimumDistToEnemies > 70 && minimumDistToEnemies < 500)
		{
			BWAPI::Broodwar->printf("Turning on potential field");
			_tactic.ExecuteTactic((*u),_units);
		}

		if((*u)->exists() && !((LocationToMoveTo.x() == 1 && LocationToMoveTo.y() == 1) || (LocationToMoveTo.x() == 0 && LocationToMoveTo.y() == 0)) && (numberOfUnits > 4))
		{
			if(
				((*u)->getPosition().x() > (LocationToMoveTo.x()-50)) &&
				((*u)->getPosition().x() < (LocationToMoveTo.x()+50)) &&
				((*u)->getPosition().y() > (LocationToMoveTo.y()-50)) &&
				((*u)->getPosition().y() < (LocationToMoveTo.y()+50))
				)
			{
				BWAPI::Broodwar->printf("At location");
				//LocationToMoveTo = BWAPI::Position(1,1);
			}
			else
			{
				BWAPI::Broodwar->printf("move to %d , %d",LocationToMoveTo.x(),LocationToMoveTo.y());
				(*u)->move(LocationToMoveTo,false);
			}
		}
	}
	
}
int Squad::GetSize()
{
	int number = 0;
	for(std::set<BWAPI::Unit*>::iterator u = _units.begin(); u != _units.end(); u++)
	{
		if((*u)->exists())
		{
			number++;
		}
	}
	return number;
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