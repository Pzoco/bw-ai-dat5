#include "TacticsManager.h"
#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>
#include "UnitHelper.h"
#include "MathHelper.h"

//Does a mapping between unittypes and lists
std::map<BWAPI::UnitType,std::list<Squad>> squads;

TacticsManager* TacticsManager::tacticsManager = 0;
TacticsManager::TacticsManager(){}
TacticsManager* TacticsManager::GetInstance()
{
	if(tacticsManager==NULL)
	{
		tacticsManager = new TacticsManager();
	}
	return tacticsManager;
}

void TacticsManager::AddSquad(Squad squad)
{
	squads[squad.GetUnitType()].push_back(squad);
}
void TacticsManager::RemoveSquad(Squad squad)
{
	for(std::list<Squad>::iterator s=squads[squad.GetUnitType()].begin();s!=squads[squad.GetUnitType()].end();s++)
	{
		if((&(*s)) == &(squad))
		{
			squads[squad.GetUnitType()].erase(s);
			break;
		}
	}
}
void TacticsManager::Update()
{
	for(std::map<BWAPI::UnitType,std::list<Squad>>::iterator i = squads.begin(); i != squads.end(); i++ ) 
	{
		for each(Squad squad in i->second)
		{
			squad.ExecuteTactics();
		}
	}
}
void TacticsManager::AssignToSquad(BWAPI::Unit* unit)
{
	if(UnitHelper::IsOffensiveType(unit->getType()))
	{
		if(squads[unit->getType()].empty())
		{
			//Should use the specific tactic not basetactic
			Squad s = Squad(unit,BaseTactic());
			squads[unit->getType()].push_back(s);
		}
		else
		{
			//Find a squad most suitable compared to the distance
			Squad bestSquad;
			int bestDistance=100000;
			
			for each(Squad s in squads[unit->getType()])
			{
				int squadCenterDistance = unit->getDistance(s.GetSquadCenter());
				if(bestDistance > squadCenterDistance)
				{
					bestSquad = s;
					bestDistance = squadCenterDistance;
				}
			}
			bestSquad.AddUnit(unit);			
		}
	}
}
void TacticsManager::AssignToSquads(std::set<BWAPI::Unit*> units)
{
	for each(BWAPI::Unit* unit in units)
	{
		AssignToSquad(unit);
	}
}
void TacticsManager::UnitKilled(BWAPI::Unit *unit)
{
	for(std::map<BWAPI::UnitType,std::list<Squad>>::iterator i = squads.begin(); i != squads.end(); i++ ) 
	{
		for each(Squad squad in i->second)
		{
			squad.RemoveUnit(unit);
		}
	}
}



int TacticsManager::GetNumberOfUnits(BWAPI::UnitType type)
{
	if(UnitHelper::IsOffensiveType(type))
	{
		int number= 0;
		for each(Squad squad in squads[type])
		{
			number+=squad.GetSize();
		}
		return number;
	}
	return 0;
}
