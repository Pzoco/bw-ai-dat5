#include "BaseTactic.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <math.h>
#include "MathHelper.h"

using namespace BWAPI;
BWAPI::Unit* _unit;

BaseTactic::BaseTactic()
{
}
#pragma region PF variables
struct BaseTactic::Variables
{
	int FORCEALLY;
	int FORCESQUAD;
	int FORCEMAXDIST;
	int FORCECOOLDOWN;
	int FORCEEDGE;
	int SQUADDISTANCE_CONSTANT;
	int ALLYDISTANCE_CONSTANT;
	int EDGESDISTANCE_CONSTANT;
};
BaseTactic::Variables _variables;
#pragma endregion PF variables
#pragma region PF struct1
struct BaseTactic::PotentialFieldParameters
{
	int da;//distance to closed ally unit.
	int ds;//distance from center of army to unit.
	int sv;//units maximum shooting range. -1 if no wepaon for this type.
	int sva;//units maximum shooting range for air. -1 if no wepaon for this type.
	int de;//distance to enemy.
	bool wr;//boolean denoting whether or not the weapons are ready to fire.
	int dc;//distance to cliff or edge.
	BWAPI::Position squadPos; //position on the squad

};
#pragma endregion PF struct1
#pragma region PF InitializeParameters
void BaseTactic::InitializeParameters(PotentialFieldParameters &parameters,Variables &variables, std::set<BWAPI::Unit*> myUnits)
{
	variables.FORCEALLY = 5;
	variables.FORCESQUAD = 5;
	variables.FORCEMAXDIST = 5;
	variables.FORCECOOLDOWN = 5;
	variables.FORCEEDGE = 5;
	variables.SQUADDISTANCE_CONSTANT = 50;
	variables.ALLYDISTANCE_CONSTANT = 25;
	variables.EDGESDISTANCE_CONSTANT = 5;

	// finding unit position and setting it to the center of the matrix.
	Position centerPos = _unit->getPosition();
	//distance to nearest ally unit.
	//parameters.da is calculated in MathHelper::GetDistanceToNearestAlly();
	
	//distance to center of this unit's squad.
	parameters.squadPos = MathHelper::GetSquadCenterPosition(myUnits);
	parameters.ds = centerPos.getApproxDistance(parameters.squadPos);
	//BWAPI::Broodwar->drawCircle(CoordinateType::Map,squadX,squadY,10,Colors::Green,true);

	//unit's maximum shooting range. -1 if no wepaon of this type.
	if(_unit->getType().groundWeapon() != BWAPI::WeaponTypes::None)
		parameters.sv = _unit->getType().groundWeapon().maxRange();
	else
		parameters.sv = -1;
	//unit's maximum shooting range for air. -1 if no wepaon of this type.
	if(_unit->getType().airWeapon() != BWAPI::WeaponTypes::None)
		parameters.sva = _unit->getType().airWeapon().maxRange();
	else
		parameters.sva = -1;
	//distance to enemy.
	parameters.de = MathHelper::GetDistanceToNearestEnemy(centerPos,centerPos);

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
BaseTactic::PotentialFieldParameters _parameters;
#pragma region CalculateAllyPotential
double BaseTactic::CalculateAllyPotential(BWAPI::Position pos)
{
	_parameters.da = MathHelper::GetDistanceToNearestAlly(pos,_unit->getID());
	//BWAPI::Broodwar->printf("_parameters.da is %d",_parameters.da);
	//BWAPI::Broodwar->printf("da = %d - ", _parameters.da);
	if(_parameters.da > _variables.ALLYDISTANCE_CONSTANT)
	{
		//BWAPI::Broodwar->printf("_parameters.da > ALLYDISTANCE_CONSTANT - return 0.0");
		return 0.0;
	}
	else if(_parameters.da == _variables.ALLYDISTANCE_CONSTANT)
	{
		//BWAPI::Broodwar->printf("_parameters.da == ALLYDISTANCE_CONSTANT - return %d",(-1*FORCE)/_parameters.da);
		return (-1*_variables.FORCEALLY);
	}
	else
	{
		//BWAPI::Broodwar->printf("else - return -5");

		double work = (double)(-1*_variables.FORCEALLY)/(double)_parameters.da;
		return work;
	}
}
#pragma endregion CalculateAllyPotential
#pragma region CalculateEnemyPotential
double BaseTactic::CalculateEnemyPotential()
{
	//Not written
	return 0.0;
}
#pragma endregion CalculateEnemyPotential
#pragma region CalculateSquadCenterPotential
double BaseTactic::CalculateSquadCenterPotential(BWAPI::Position pos)
{
	int dsv = pos.getApproxDistance(_parameters.squadPos);	
	//Broodwar->drawTextMap(pos.x(),pos.y(),"%d",_parameters.ds);

	if(dsv >= _parameters.ds)
	{
		return 0;
	}
	else if(_parameters.ds > _variables.SQUADDISTANCE_CONSTANT)
	{

		int returning = (_parameters.ds - dsv )* _variables.FORCESQUAD;
		//BWAPI::Broodwar->printf("CSCP if - ds = %d, c = %d, return = %d",_parameters.ds,SQUADDISTANCE_CONSTANT,returning);
		//BWAPI::Broodwar->printf("ds = %d, f = %d, return = %d",_parameters.ds,FORCE,(double)returning);
		//Broodwar->drawTextMap(pos.x()+15,pos.y()+15,"%d",returning);


		return returning;
	}
	else
	{
		return 0;
	}
}
#pragma endregion CalculateSquadCenterPotential
#pragma region CalculateMaximumDistancePotential
double BaseTactic::CalculateMaximumDistancePotential(BWAPI::Position pos)
{
	Position centerPos = _unit->getPosition();

	//Distance from current square to closest enemy.
	int centerDist = _parameters.de;
	int localDist = MathHelper::GetDistanceToNearestEnemy(pos,centerPos);
	int distBetweenTheAboveTwo = centerPos.getApproxDistance(pos);
	int correctedDist = localDist - distBetweenTheAboveTwo;


	double potential = 0;
	if(_parameters.de == 0.0 || _parameters.de == _parameters.sv)
		potential = 0.0;
	else if(correctedDist > _parameters.sv)
		potential = double(_variables.FORCEMAXDIST * correctedDist);
	else if(correctedDist < _parameters.sv )
		potential = ( correctedDist /(-1)*_variables.FORCEMAXDIST );

	return potential;
}
#pragma endregion CalculateMaximumDistancePotential
#pragma region CalculateWeaponCoolDownPotential
double BaseTactic::CalculateWeaponCoolDownPotential(BWAPI::Position pos)
{
	if(_parameters.wr)
	{
		return 0.0;
	}
	else
	{
		Position centerPos = _unit->getPosition();
		int centerDist = _parameters.de;
		int localDist = MathHelper::GetDistanceToNearestEnemy(pos,centerPos);
		int distBetweenTheAboveTwo = centerPos.getApproxDistance(pos);
		int correctedDist = localDist - distBetweenTheAboveTwo;
		int toReturn = (-1)*correctedDist*_variables.FORCECOOLDOWN;
		Broodwar->drawTextMap(pos.x(),pos.y(),"%d",toReturn);

		return toReturn;
	}
}
#pragma endregion CalculateWeaponCoolDownPotential
#pragma region CalculateEdgesPotential
double BaseTactic::CalculateEdgesPotential()
{
	if(_parameters.dc <= _variables.EDGESDISTANCE_CONSTANT)
	{
		return (-1*_variables.FORCEEDGE)/_parameters.dc;
	}
	else
	{
		return 0.0;
	}
}
#pragma endregion CalculateEdgesPotential
#pragma region CalculatePotentialField
double BaseTactic::CalculatePotentialField(BWAPI::Position pos)
{
	double potentialOfField = 0.0;
	
	
	//potentialOfField +=  BaseTactic::CalculateAllyPotential(pos);
	//potentialOfField += BaseTactic::CalculateSquadCenterPotential(pos);
	potentialOfField += BaseTactic::CalculateMaximumDistancePotential(pos);
	//potentialOfField += BaseTactic::CalculateWeaponCoolDownPotential(pos);
	//potentialOfField = BaseTactic::CalculateEdgesPotential();
	//potentialOfField = BaseTactic::CalculateEnemyPotential();	
	//BWAPI::Broodwar->printf("potentialOfField = %d",potentialOfField);
	
	Broodwar->drawTextMap(pos.x(),pos.y(),"%d",(int)potentialOfField);
	return potentialOfField;
}
#pragma endregion CalculatePotentialField
#pragma region GetPotentialBestField
BWAPI::Position BaseTactic::GetPotentialBestField(double &currentGoalPotential, bool &allZero, std::set<BWAPI::Unit*> mySquad)
{
	BaseTactic::InitializeParameters(_parameters,_variables,mySquad);
	Position centerPosition = _unit->getPosition();
	//Calculation surround walking tiles.
	//Tilesize is 48, because a normal tile is 32 and plus the half of the centertile - 32+32/2 = 48
	std::list<BWAPI::Position> positions = MathHelper::GetSurroundingPositions(centerPosition.x(),centerPosition.y(),48);
	BWAPI::Position bestPosition = BWAPI::Position(1,1);
	double bestPotential = -1000.0;

	for each(BWAPI::Position position in positions)
	{
		double currentPotential = CalculatePotentialField(position);
		//BWAPI::Broodwar->printf("MyPos = %d,%d, SuPos = %d,%d, ptf = %f",_unit->getPosition().x(),_unit->getPosition().y(),position.x(),position.y(),currentPotential);
		//BWAPI::Broodwar->printf("bestPotential = %d. currentPotential = %d",bestPotential,currentPotential);
		if(bestPotential < currentPotential)
		{
			bestPosition = position;
			bestPotential = currentPotential;


			int a = position.x();
			int b = position.y();
			//BWAPI::Broodwar->printf("bestPosition changed to %d,%d.. Potential is %d",a,b,currentPotential);
		}
		if(currentPotential != 0.0)
		{
			allZero = false;
		}
	}
	currentGoalPotential = bestPotential;
	return bestPosition;
}
#pragma endregion GetPotentialBestField
#pragma region ExecuteTactic
void BaseTactic::ExecuteTactic(BWAPI::Unit* unit,std::set<BWAPI::Unit*> theSquad)
{
	_unit = unit;
	double currentGoalPotential = 0;
	bool allZero = true;
	Position currentGoal = GetPotentialBestField(currentGoalPotential, allZero, theSquad);

	//BWAPI::Broodwar->printf("Goal potential = %d",currentGoalPotential);

	if(allZero == false)
	{
		unit->move(currentGoal);
	}
	
}
#pragma endregion ExecuteTactic
BaseTactic::Variables BaseTactic::GetVariables()
{
	return _variables;
}
void BaseTactic::SetVariables(BaseTactic::Variables vars)
{
	_variables = vars;
}