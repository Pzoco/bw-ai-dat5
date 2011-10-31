#include "UnitAgent.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <math.h>
#include "MathHelper.h"

using namespace BWAPI;
BWAPI::Unit* _unit;
BWAPI::Position _currentGoal;


UnitAgent::UnitAgent(BWAPI::Unit* unit)
{
	_unit = unit;
}
#pragma region PF parameters
#pragma region PF constants
const int FORCE = 25;
const int SQUADDISTANCE_CONSTANT = 30;
const int ALLYDISTANCE_CONSTANT = 30;
const int EDGESDISTANCE_CONSTANT = 30;
#pragma endregion PF constants
#pragma region PF struct1
struct UnitAgent::PotentialFieldParameters
{
	int f;//force.
	int da;//distance to closed ally unit.
	int ds;//distance from center of army to unit.
	int sv;//units maximum shooting range. -1 if no wepaon for this type.
	int sva;//units maximum shooting range for air. -1 if no wepaon for this type.
	int de;//distance to enemy.
	bool wr;//boolean denoting whether or not the weapons are ready to fire.
	int dc;//distance to cliff or edge.
};
#pragma endregion PF struct1
void UnitAgent::InitializeParameters(PotentialFieldParameters &parameters)
{
	// finding unit position and setting it to the center of the matrix.
	Position centerPos = _unit->getPosition();
	
	//force.
	parameters.f = FORCE;
	//distance to nearest ally unit.
	parameters.da = MathHelper::GetNearestAlly(centerPos.x(),centerPos.y());
	//distance to center of this unit's squad.
	
	/* just need to add the squad.. its not defined yet
	int squadX = 0;
	int squady = 0;
	MathHelper::GetSquadCenter(squad,squadX,squady);
	BWAPI::Position squadPos;
	squadPos.x = squadX;
	squadPos.y = squadY;
	parameters.ds = _unit->getDistance(squadPos);
	*/


	//unit's maximum shooting range. -1 if no wepaon for this type.
	if(_unit->getType().groundWeapon() != BWAPI::WeaponTypes::None)
	{
		parameters.sv = _unit->getType().groundWeapon().maxRange();
	}
	else
	{
		parameters.sv = -1;
	}
	//unit's maximum shooting range for air. -1 if no wepaon for this type.
	if(_unit->getType().airWeapon() != BWAPI::WeaponTypes::None)
	{
		parameters.sv = _unit->getType().airWeapon().maxRange();
	}
	else
	{
		parameters.sv = -1;
	}
	//distance to enemy.
	parameters.de = MathHelper::GetNearestEnemy(centerPos.x(),centerPos.y());
	//boolean denoting whether or not the weapons are ready to fire.
	if(_unit->getAirWeaponCooldown() == 0 && _unit->getGroundWeaponCooldown() == 0)
	{
		parameters.wr = true;
	}
	else
	{
		parameters.wr = false;
	}
	//distance to cliff or edge.
	parameters.dc = 0;
}
UnitAgent::PotentialFieldParameters _parameters;
#pragma endregion PF parameters
#pragma region CalculatePotential functions
double UnitAgent::CalculateAllyPotential()
{
	if(_parameters.da > ALLYDISTANCE_CONSTANT)
	{
		return 0.0;
	}
	else if(_parameters.da == ALLYDISTANCE_CONSTANT)
	{
		return (-1*FORCE)/_parameters.da;
	}
	else
	{
		return (-1*FORCE);
	}
}
double UnitAgent::CalculateEnemyPotential()
{
	//Not written
	return 0.0;
}
double UnitAgent::CalculateSquadCenterPotential()
{
	if(_parameters.ds > SQUADDISTANCE_CONSTANT)
	{
		return FORCE*_parameters.ds;
	}
	else
	{
		return 0.0;
	}
}
double UnitAgent::CalculateMaximumDistancePotential()
{
	//Needs fixing in the report
	return 0.0;
}
double UnitAgent::CalculateWeaponCoolDownPotential()
{
	if(_parameters.wr)
	{
		return 0.0;
	}
	else
	{
		return (-1*FORCE);
	}
}
double UnitAgent::CalculateEdgesPotential()
{
	if(_parameters.dc <= EDGESDISTANCE_CONSTANT)
	{
		return (-1*FORCE)/_parameters.dc;
	}
	else
	{
		return 0.0;
	}
}

double UnitAgent::CalculatePotentialField(BWAPI::Position)
{
	double potentialOfField = 0.0;
	potentialOfField = UnitAgent::CalculateAllyPotential();
	potentialOfField = UnitAgent::CalculateEnemyPotential();
	potentialOfField = UnitAgent::CalculateSquadCenterPotential();
	potentialOfField = UnitAgent::CalculateMaximumDistancePotential();
	potentialOfField = UnitAgent::CalculateWeaponCoolDownPotential();
	potentialOfField = UnitAgent::CalculateEdgesPotential();

	return potentialOfField;
}
BWAPI::Position UnitAgent::GetPotentialBestField()
{
	UnitAgent::InitializeParameters(_parameters);
	Position centerPosition = _unit->getPosition();
	//Calculation surround walking tiles.
	//Tilesize is 48, because a normal tile is 32 and plus the half of the centertile - 32+32/2 = 48
	std::list<BWAPI::Position> positions = MathHelper::GetSurroundingPositions(centerPosition.x(),centerPosition.y(),48);
	BWAPI::Position bestPosition;
	double bestPotential = -1000.0;
	for each(BWAPI::Position position in positions)
	{
		double currentPotential = CalculatePotentialField(position);
		if(bestPotential < currentPotential)
		{
			bestPosition = position;
			bestPotential = currentPotential;
		}
	}
	return bestPosition;
}
#pragma endregion CalculatePotential functions

void UnitAgent::FindAndSetNewGoal()
{
	_currentGoal = GetPotentialBestField();
	_unit->rightClick(_currentGoal);
}