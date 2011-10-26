#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class UnitAgent
{
public:
	UnitAgent(BWAPI::Unit* unit);
	virtual double CalculateAllyPotential();
	virtual double CalculateEnemyPotential();
	virtual double UnitAgent::CalculateSquadCenterPotential();
	virtual double UnitAgent::CalculateMaximumDistancePotential();
	virtual double UnitAgent::CalculateWeaponCoolDownPotential();
	virtual double UnitAgent::CalculateEdgesPotential();
	virtual double UnitAgent::CalculatePotentialField();
};
