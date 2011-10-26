#include "UnitAgent.h"
#include <BWAPI.h>
#include <BWTA.h>

#pragma region CalculatePotential functions
double UnitAgent::CalculateAllyPotential()
{
	return 0.0;
}
double UnitAgent::CalculateEnemyPotential()
{
	return 0.0;
}
double UnitAgent::CalculateSquadCenterPotential()
{
	return 0.0;
}
double UnitAgent::CalculateMaximumDistancePotential()
{
	return 0.0;
}
double UnitAgent::CalculateWeaponCoolDownPotential()
{
	return 0.0;
}
double UnitAgent::CalculateEdgesPotential()
{
	return 0.0;
}

double UnitAgent::CalculatePotentialField()
{
	double potential = 0.0;
	potential +=CalculateAllyPotential();
	potential +=CalculateEnemyPotential();
	//etc.... only the idea right now
	return potential;
}
#pragma endregion CalculatePotential functions

BWAPI::Unit* _unit;

UnitAgent::UnitAgent(BWAPI::Unit* unit)
{
	_unit = unit;
}

