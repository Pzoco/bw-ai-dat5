#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class UnitAgent
{
public:
	UnitAgent(BWAPI::Unit* unit);
	virtual struct PotentialField;
	virtual void CalculateAllyPotential(PotentialField &field);
	virtual void CalculateEnemyPotential();
	virtual void UnitAgent::CalculateSquadCenterPotential();
	virtual void UnitAgent::CalculateMaximumDistancePotential();
	virtual void UnitAgent::CalculateWeaponCoolDownPotential();
	virtual void UnitAgent::CalculateEdgesPotential();
	virtual void UnitAgent::CalculatePotentialField();
	virtual void UnitAgent::Initialize(PotentialField &field);
};
