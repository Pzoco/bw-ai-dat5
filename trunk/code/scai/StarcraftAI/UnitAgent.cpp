#include "UnitAgent.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <math.h>
#include "MathHelper.h"

using namespace BWAPI;
BWAPI::Unit* _unit;
BWAPI::Position _currentGoal;

UnitAgent::UnitAgent()
{
}
UnitAgent::UnitAgent(BWAPI::Unit* unit)
{
	_unit = unit;
}
BWAPI::Unit* UnitAgent::GetUnit()
{
	return _unit;
}
#pragma region PF parameters
#pragma region PF constants
const int FORCE = 5;
const int SQUADDISTANCE_CONSTANT = 5;
const int ALLYDISTANCE_CONSTANT = 5;
const int EDGESDISTANCE_CONSTANT = 5;
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
#pragma region PF InitializeParameters
void UnitAgent::InitializeParameters(PotentialFieldParameters &parameters)
{
	// finding unit position and setting it to the center of the matrix.
	Position centerPos = _unit->getPosition();
	
	//force.
	parameters.f = FORCE;
	//distance to nearest ally unit.
	//parameters.da is calculated in MathHelper::GetNearestAlly();
	
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
#pragma endregion PF InitializeParameters
UnitAgent::PotentialFieldParameters _parameters;
#pragma endregion PF parameters
#pragma region CalculatePotential functions
double UnitAgent::CalculateAllyPotential(BWAPI::Position pos)
{
	_parameters.da = MathHelper::GetNearestAlly(pos.x(),pos.y(),_unit->getID());
	//BWAPI::Broodwar->printf("_parameters.da is %d",_parameters.da);
	//BWAPI::Broodwar->printf("da = %d - ", _parameters.da);
	if(_parameters.da > ALLYDISTANCE_CONSTANT)
	{
		//BWAPI::Broodwar->printf("_parameters.da > ALLYDISTANCE_CONSTANT - return 0.0");
		return 0.0;
	}
	else if(_parameters.da == ALLYDISTANCE_CONSTANT)
	{
		//BWAPI::Broodwar->printf("_parameters.da == ALLYDISTANCE_CONSTANT - return %d",(-1*FORCE)/_parameters.da);
		return (-1*FORCE);
	}
	else
	{
		//BWAPI::Broodwar->printf("else - return -5");

		double work = (double)(-1*FORCE)/(double)_parameters.da;
		return work;
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

double UnitAgent::CalculatePotentialField(BWAPI::Position pos)
{
	double potentialOfField = 0.0;
	
	
	potentialOfField =  UnitAgent::CalculateAllyPotential(pos);
	//potentialOfField = UnitAgent::CalculateEnemyPotential();
	//potentialOfField = UnitAgent::CalculateSquadCenterPotential();
	//potentialOfField = UnitAgent::CalculateMaximumDistancePotential();
	//potentialOfField = UnitAgent::CalculateWeaponCoolDownPotential();
	//potentialOfField = UnitAgent::CalculateEdgesPotential();
	//BWAPI::Broodwar->printf("potentialOfField = %d",potentialOfField);
	return potentialOfField;
}
BWAPI::Position UnitAgent::GetPotentialBestField(double &currentGoalPotential, bool &allZero)
{
	UnitAgent::InitializeParameters(_parameters);
	Position centerPosition = _unit->getPosition();
	//Calculation surround walking tiles.
	//Tilesize is 48, because a normal tile is 32 and plus the half of the centertile - 32+32/2 = 48
	std::list<BWAPI::Position> positions = MathHelper::GetSurroundingPositions(centerPosition.x(),centerPosition.y(),48);
	BWAPI::Position bestPosition = BWAPI::Position(1,1);
	double bestPotential = -1000.0;

	for each(BWAPI::Position position in positions)
	{
		double currentPotential = CalculatePotentialField(position);
		BWAPI::Broodwar->printf("MyPos = %d,%d, SuPos = %d,%d, ptf = %f",_unit->getPosition().x(),_unit->getPosition().y(),position.x(),position.y(),currentPotential);
		//BWAPI::Broodwar->printf("bestPotential = %d. currentPotential = %d",bestPotential,currentPotential);
		if(bestPotential < currentPotential)
		{
			bestPosition = position;
			bestPotential = currentPotential;


			int a = position.x();
			int b = position.y();
			//BWAPI::Broodwar->printf("bestPosition changed to %d,%d.. Potential is %d",a,b,currentPotential);
		}
		if(currentPotential != 0)
		{
			allZero = false;
		}
	}
	currentGoalPotential = bestPotential;
	return bestPosition;
}
#pragma endregion CalculatePotential functions

void UnitAgent::FindAndSetNewGoal()
{
	double currentGoalPotential = 0;
	bool allZero = true;
	_currentGoal = GetPotentialBestField(currentGoalPotential, allZero);

	//BWAPI::Broodwar->printf("Goal potential = %d",currentGoalPotential);

	if(allZero == false)
	{
		_unit->rightClick(_currentGoal);
	}
	
}