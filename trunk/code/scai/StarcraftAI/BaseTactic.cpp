#include "BaseTactic.h"
#include "MathHelper.h"
#include "ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <math.h>
#include "Source/StarcraftAI.h"
#include "ReinforcementLearning.h"

using namespace BWAPI;
BWAPI::Unit* _unit;
BaseTactic::BaseTactic()
{
}
struct BaseTactic::Variables
{
	//This contain all the different forces and variables the reinforsment learning should change
	double FORCEALLY;
	double FORCESQUAD;
	double FORCEMAXDIST1;
	double FORCEMAXDIST2;
	double FORCECOOLDOWN;
	double FORCEEDGE;
	double FORCENEMY;
	int SQUADDISTANCE_CONSTANT;
	int ALLYDISTANCE_CONSTANT;
	int EDGESDISTANCE_CONSTANT;
}; 

BaseTactic::Variables _variables;

struct BaseTactic::PotentialFieldParameters
{
	int da;//distance to closed ally unit.
	int ds;//distance from center of army to unit.
	int sv;//units maximum shooting range. -1 if no weapon for this type.
	int sva;//units maximum shooting range for air. -1 if no weapon for this type.
	int de;//distance to enemy.
	bool wr;//boolean denoting whether or not the weapons are ready to fire.
	int dc;//distance to cliff or edge.
	BWAPI::Position squadPos; //position on the squad

};

struct MathHelper::ReturningUnit
{
	BWAPI::Unit* ClosestEnemy;
	bool exist;
};
BaseTactic::PotentialFieldParameters _parameters;
BaseTactic::PotentialFieldParameters _qParameters;
void BaseTactic::InitializeParameters(std::set<BWAPI::Unit*> myUnits)
{
	//Setting all the variables, this should later be done by the reinforcement learning
	_variables.FORCEALLY = StarcraftAI::reinforcementLearning.GetForceAlly();
	_variables.FORCESQUAD = StarcraftAI::reinforcementLearning.GetForceSquad();
	_variables.FORCEMAXDIST1 = StarcraftAI::reinforcementLearning.GetForceMaxDist1();
	_variables.FORCEMAXDIST2 = StarcraftAI::reinforcementLearning.GetForceMaxDist2();
	_variables.FORCECOOLDOWN = StarcraftAI::reinforcementLearning.GetForceCooldown();
	_variables.FORCEEDGE = StarcraftAI::reinforcementLearning.GetForceEdge();
	
 
	//_variables.FORCENEMY = 1;
	//StarcraftAI::reinforcementLearning.
	_variables.SQUADDISTANCE_CONSTANT = 100;
	_variables.ALLYDISTANCE_CONSTANT = 50;
	_variables.EDGESDISTANCE_CONSTANT = 250;

	// finding unit position and setting it to the center of the matrix.
	Position unitPos = _unit->getPosition();
	//distance to nearest ally unit.
	//_parameters.da is calculated in MathHelper::GetDistanceToNearestAlly();
	
	//distance to center of this unit's squad.
	_parameters.squadPos = MathHelper::GetSquadCenterPosition(myUnits);
	_parameters.ds = unitPos.getApproxDistance(_parameters.squadPos);
	//BWAPI::Broodwar->drawCircle(CoordinateType::Map,squadX,squadY,10,Colors::Green,true);

	//unit's maximum shooting range. -1 if no weapon of this type.
	if(_unit->getType().groundWeapon() != BWAPI::WeaponTypes::None)
		_parameters.sv = _unit->getType().groundWeapon().maxRange();
	else
		_parameters.sv = -1;
	//unit's maximum shooting range for air. -1 if no weapon of this type.
	if(_unit->getType().airWeapon() != BWAPI::WeaponTypes::None)
		_parameters.sva = _unit->getType().airWeapon().maxRange();
	else
		_parameters.sva = -1;
	//distance to enemy.
	//BWAPI::Broodwar->printf("calling GetDistanceToNearestEnemy");
	_parameters.de = MathHelper::GetDistanceToNearestEnemy(unitPos);

	//boolean denoting whether or not the weapons are ready to fire.
	if(_unit->getAirWeaponCooldown() == 0 && _unit->getGroundWeaponCooldown() == 0)
	{
		_parameters.wr = true;
	}
	else
	{
		_parameters.wr = false;
	}
	//distance to cliff or edge.
	_parameters.dc = 0;
}


double BaseTactic::CalculateAllyPotential(BWAPI::Position pos)
{

	int dua = MathHelper::GetDistanceToNearestAlly(pos,_unit->getID());
	_parameters.da = MathHelper::GetDistanceToNearestAlly(_unit->getPosition(),_unit->getID());
	double potential = 0.0;
	if(_parameters.da > _variables.ALLYDISTANCE_CONSTANT)
		potential = 0.0;
	else if(_parameters.da == _variables.ALLYDISTANCE_CONSTANT)
		potential = (-1)*_variables.FORCEALLY*(double)(_parameters.da - dua + _parameters.da);
	else
		potential = (-1)*(double)_variables.FORCEALLY*(double)(_parameters.da - dua + _parameters.da);

	//BWAPI::Broodwar->printf("%d, %d",(int)potential,(int)(_parameters.da - dua + _parameters.da) );
	return potential;
}

double BaseTactic::CalculateSquadCenterPotential(BWAPI::Position pos)
{
	//First we need to find the distance from the current tile to the squad center.
	int dsv = pos.getApproxDistance(_parameters.squadPos);	
	double potential = 0.0;

	//then calculate the potiential depending on the functions specefied in the report
	if(dsv >= _parameters.ds)
		potential = 0.0;
	else if(_parameters.ds > _variables.SQUADDISTANCE_CONSTANT)
		potential = (_parameters.ds - dsv )* _variables.FORCESQUAD;
	else
		potential = 0.0;

	//BWAPI::Broodwar->printf("%d, %d",(int)dsv,(int)_parameters.ds );
	//BWAPI::Broodwar->drawCircleMap(_parameters.squadPos.x(),_parameters.squadPos.y(),15,BWAPI::Colors::Green,true);
	return potential;
}

double BaseTactic::CalculateMaximumDistancePotential(BWAPI::Position pos)
{
	//Getting the units position
	Position unitPos = _unit->getPosition();

	//Distance from current square to closest enemy.
	int distanceToEnemyFromUnit = _parameters.de;
	int distanceToEnemyFromCurrentTile = MathHelper::GetDistanceToNearestEnemy(pos);
	//Taking into account the distance from the unit to the current tile.
	int correctedDistance = (_parameters.de - distanceToEnemyFromCurrentTile + _parameters.de);

	//then calculate the potiential depending on the functions specefied in the report
	double potential = 0.0;
	if(_parameters.de == 0.0 || _parameters.de == _parameters.sv)
		potential = 0.0;
	else if(distanceToEnemyFromCurrentTile > _parameters.sv)
		potential = (_variables.FORCEMAXDIST1 * correctedDistance);
	else if(distanceToEnemyFromCurrentTile < _parameters.sv )
		potential = (-1)*(_variables.FORCEMAXDIST2 * correctedDistance);

	return potential;
}
double BaseTactic::CalculateWeaponCoolDownPotential(BWAPI::Position pos)
{
	//This returns a negative potential in the direction of the enemy units if the weapons is not ready
	double potential = 0.0;
	if(_parameters.wr){}
	else
	{
		int distanceToEnemyFromUnit = _parameters.de;
		int distanceToEnemyFromCurrentTile = MathHelper::GetDistanceToNearestEnemy(pos);
		int correctedDistance = (_parameters.de - distanceToEnemyFromCurrentTile + _parameters.de);
		potential = (-1)*correctedDistance*_variables.FORCECOOLDOWN;
		
	}
	//BWAPI::Broodwar->printf("%f",potential);
	return potential;
}

double BaseTactic::CalculateEdgesPotential(BWAPI::Position pos)
{
	if(ScoutingManager::IsMapAnalyzed())
	{
		int duc = (int)MathHelper::GetDistanceBetweenPositions(BWTA::getNearestUnwalkablePosition(pos),pos);
		_parameters.dc = (int)MathHelper::GetDistanceBetweenPositions(BWTA::getNearestUnwalkablePosition(_unit->getPosition()),_unit->getPosition());
		//Broodwar->drawTextMap(pos.x(),pos.y(),"%d",(int)((-1)*(_variables.FORCEEDGE*(_parameters.dc - duc + _parameters.dc))));
		//Broodwar->printf("Distance is %d",_parameters.dc);
		if(_parameters.dc <= _variables.EDGESDISTANCE_CONSTANT)
		{
			return (-1)*(_variables.FORCEEDGE*(_parameters.dc - duc + _parameters.dc));
		}
		else
		{
			return 0.0;
		}
	}
	return 0.0;
}
double BaseTactic::CalculateQPotentialField(BWAPI::Position pos, bool print)
{
	double potential = 0.0;
	double ally = 0.0;
	double edge = 0.0;
	double cool = 0.0;
	double maxdist1 = 0.0;
	double maxdist2 = 0.0;
	double squad = 0.0;
	double allyQ = 0.0;
	double edgeQ = 0.0;
	double coolQ = 0.0;
	double maxdist1Q = 0.0;
	double maxdist2Q = 0.0;
	double squadQ = 0.0;
	//EDGE
	if(ScoutingManager::IsMapAnalyzed())
	{
		_qParameters.dc = (int)MathHelper::GetDistanceBetweenPositions(BWTA::getNearestUnwalkablePosition(pos),pos);
		edge += (-1*_variables.FORCEEDGE)*_qParameters.dc;
		edgeQ += _qParameters.dc;
	}
	//COOLDOWN
	Position unitPos = _unit->getPosition();
	_qParameters.de = MathHelper::GetDistanceToNearestEnemy(pos);
	int distanceToEnemyFromUnit = _qParameters.de;
	int distanceToEnemyFromCurrentTile = MathHelper::GetDistanceToNearestEnemy(pos);
	int correctedDistance = (_qParameters.de - distanceToEnemyFromCurrentTile + _qParameters.de);
	
	cool += (-1)*(double)correctedDistance*_variables.FORCECOOLDOWN;
	coolQ += (-1)*(double)correctedDistance;
	//MAXDIST
	maxdist1 += (_variables.FORCEMAXDIST1 * correctedDistance);
	maxdist2 += (-1)*(_variables.FORCEMAXDIST2 * correctedDistance);
	maxdist1Q += (correctedDistance);
	maxdist2Q += (-1)*(correctedDistance);
	
	
	//SQUADCENTER
	int dsv = pos.getApproxDistance(_parameters.squadPos);	
	squad += (double)(dsv)* _variables.FORCESQUAD; 
	squadQ += (double)(dsv);
	/*
	Removed :
	squad += (double)(_parameters.ds - dsv )* _variables.FORCESQUAD;
	squadQ += (double)(_parameters.ds - dsv );
	else it becomes 0 from time to time and this causes the CalculateTheta to become 0
	*/

	//ALLY
	_parameters.da = MathHelper::GetDistanceToNearestAlly(pos,_unit->getID());
	ally += (-1)*(double)_variables.FORCEALLY*(double)_parameters.da;
	allyQ += (-1)*(double)_parameters.da;

	potential = edge + cool + maxdist1 + maxdist2 + squad + ally;
	//BWAPI::Broodwar->printf("%f",potential);
	if(print)
	{
		StarcraftAI::reinforcementLearning.WriteValueToBuffer(allyQ, false);
		StarcraftAI::reinforcementLearning.WriteValueToBuffer(squadQ, false);
		StarcraftAI::reinforcementLearning.WriteValueToBuffer(maxdist1Q, false);
		StarcraftAI::reinforcementLearning.WriteValueToBuffer(maxdist2Q, false);
		StarcraftAI::reinforcementLearning.WriteValueToBuffer(coolQ, false);
		StarcraftAI::reinforcementLearning.WriteValueToBuffer(edgeQ, false); 


	}
	//Broodwar->drawTextMap(pos.x(),pos.y(),"%d",(int)potential);
	//BWAPI::Broodwar->printf("%d",(int)squad);
	//BWAPI::Broodwar->printf("e %f, c %f, m1 %f, m2 %f, s %f, a %f, p %f",edgeQ,coolQ,maxdist1Q,maxdist2Q,squadQ,allyQ,potential);
	return potential;
}
double BaseTactic::CalculatePotentialField(BWAPI::Position pos)
{
	//Calculating the potential for the current tile by calling all the different functions
	double totalPotentialForCurrentTile = 0.0;
	totalPotentialForCurrentTile +=  BaseTactic::CalculateAllyPotential(pos);
	totalPotentialForCurrentTile += BaseTactic::CalculateSquadCenterPotential(pos);
	totalPotentialForCurrentTile += BaseTactic::CalculateMaximumDistancePotential(pos);
	totalPotentialForCurrentTile += BaseTactic::CalculateWeaponCoolDownPotential(pos);
	totalPotentialForCurrentTile += BaseTactic::CalculateEdgesPotential(pos);
	
	// The line below is optional, it will print the potential to the screen.
	//Broodwar->drawTextMap(pos.x(),pos.y(),"%d",(int)totalPotentialForCurrentTile);
	return totalPotentialForCurrentTile;
}

BWAPI::Position BaseTactic::GetBestPositionBasedOnPotential(std::set<BWAPI::Unit*> mySquad)
{
	BaseTactic::InitializeParameters(mySquad);
	Position centerPosition = _unit->getPosition();
	//Calculation surround walking tiles.
	//Tilesize is 48, because a normal tile is 32 and plus the half of the center tile - 32+32/2 = 48
	std::list<BWAPI::Position> positions = MathHelper::GetSurroundingPositions(centerPosition,48);
	BWAPI::Position bestPosition = BWAPI::Position(1,1);

	//handling the special case where the tile we are now have a negative posistion and some other tile have 0
	double centerPositionPotential = 0.0;

	double bestPotential = -1000.0;

	for each(BWAPI::Position position in positions)
	{
		double currentPotential = CalculatePotentialField(position);
		
		//Setting bestPotential to be the best potential
		if(bestPotential < currentPotential)
		{
			bestPosition = position;
			bestPotential = currentPotential;
		}
		//Handling the special case
		if(position == centerPosition)
		{
			centerPositionPotential = currentPotential;
		}
	}

	/*
		Save bestPotential and pretend to be at bestPosition
	*/
	double currentQ = CalculateQPotentialField(centerPosition,true);
	StarcraftAI::reinforcementLearning.WriteValueToBuffer(currentQ, false);
	double nextQ = CalculateQPotentialField(bestPosition,false);
	StarcraftAI::reinforcementLearning.WriteValueToBuffer(nextQ, false);
	double reward = StarcraftAI::reinforcementLearning.CalculateReward(mySquad); 
	StarcraftAI::reinforcementLearning.WriteValueToBuffer(reward, false);
	
	//StarcraftAI::reinforcementLearning.WriteRewardFile(currentQ);
	//StarcraftAI::reinforcementLearning.WriteRewardFile(nextQ);
	//StarcraftAI::reinforcementLearning.WriteRewardFile(reward);
	//BWAPI::Broodwar->printf("cQ = %d, nQ = %d, re = %d",(int)currentQ,(int)nextQ,(int)reward);
	
	/*
		Figure out what to return
	*/	
	if(bestPotential == 0.0 && centerPositionPotential == 0.0)
		return centerPosition;
	else
		return bestPosition;
}



void BaseTactic::ExecuteTactic(BWAPI::Unit* unit,std::set<BWAPI::Unit*> theSquad)
{
	//Settint the current unit we work on.
	_unit = unit;
	
	//Calculating the potential
	Position currentGoal = GetBestPositionBasedOnPotential(theSquad);
	MathHelper::ReturningUnit potentialTarget = MathHelper::GetNearestEnemy(_unit->getPosition());

	if(potentialTarget.exist)
	{
		if(_unit->isInWeaponRange(potentialTarget.ClosestEnemy))
		{
			_unit->attack(potentialTarget.ClosestEnemy);
		}
	}


	//If there is nothing to do just dont do anything aka, GetBestPositionBasedOnPotential return the tile we are currently on.
	//This can happen in two cases, first the current tile we are on is the best, or all tiles are 0.

	//if not isAttackFrame

	if(currentGoal != _unit->getPosition())
		unit->move(currentGoal);
	
}

BaseTactic::Variables BaseTactic::GetVariables()
{
	return _variables;
}
void BaseTactic::SetVariables(BaseTactic::Variables vars)
{
	_variables = vars;
}