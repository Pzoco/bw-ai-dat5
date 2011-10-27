#include "UnitAgent.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <math.h>
#include "MathHelper.h"

using namespace BWAPI;
BWAPI::Unit* _unit;

UnitAgent::UnitAgent(BWAPI::Unit* unit)
{
	_unit = unit;
}


#pragma region CalculatePotential functions
#define FORCE 25
struct UnitAgent::PotentialField
{
	int Matrix[8];
	BWAPI::Position SurroundingTiles[8];
	int f;//force.
	int da;//distance to closed ally unit.
	int ds;//distance from center of army to unit.
	int sv;//units maximum shooting range.
	int de;//distance to enamy.
	bool wr;//boolean denoting whether or not the weapons are ready to fire.
	int dc;//distance to cliff or edge.
};

void UnitAgent::CalculateAllyPotential(PotentialField &field)
{
	
}
void UnitAgent::CalculateEnemyPotential()
{
	
}
void UnitAgent::CalculateSquadCenterPotential()
{
	
}
void UnitAgent::CalculateMaximumDistancePotential()
{
	
}
void UnitAgent::CalculateWeaponCoolDownPotential()
{
	
}
void UnitAgent::CalculateEdgesPotential()
{
	
}

void UnitAgent::Initialize(PotentialField &field)
{

	// finding unit position and setting it to the center of the matrix.
	Position centerPos = _unit->getPosition();
	
	//Calculation surround walking tiles.
	//Tilesize is 48, because a normal tile is 32 and plus the half of the centertile - 32+32/2 = 48
	std::list<BWAPI::Position> positions = MathHelper::GetSurroundingPositions(centerPos.x(),centerPos.y(),48);


	//force.
	field.f = FORCE;
	//distance to closed ally unit.
	field.da = MathHelper::GetNearestAlly(centerPos.x(),centerPos.y());
	//distance from center of army to unit.
	field.ds = 0;
	//units maximum shooting range.
	field.sv = 0;
	//distance to enamy.
	field.de = 0;
	//boolean denoting whether or not the weapons are ready to fire.
	if(_unit->getAirWeaponCooldown() == 0 && _unit->getGroundWeaponCooldown() == 0)
	{
		field.wr = true;
	}
	else
	{
		field.wr = false;
	}
	//distance to cliff or edge.
	field.dc = 0;
}

void UnitAgent::CalculatePotentialField()
{
	
	UnitAgent::PotentialField field;
	UnitAgent::Initialize(field);
	UnitAgent::CalculateAllyPotential(field);	
}
#pragma endregion CalculatePotential functions