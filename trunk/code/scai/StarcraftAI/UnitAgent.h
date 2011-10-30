#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class UnitAgent
{
public:
	UnitAgent(BWAPI::Unit* unit);
	virtual struct PotentialFieldParameters;
	virtual double UnitAgent::CalculateAllyPotential();
	virtual double UnitAgent::CalculateEnemyPotential();
	virtual double UnitAgent::CalculateSquadCenterPotential();
	virtual double UnitAgent::CalculateMaximumDistancePotential();
	virtual double UnitAgent::CalculateWeaponCoolDownPotential();
	virtual double UnitAgent::CalculateEdgesPotential();
	virtual double UnitAgent::CalculatePotentialField(BWAPI::Position);
	virtual void UnitAgent::InitializeParameters(PotentialFieldParameters &field);
	virtual BWAPI::Position UnitAgent::GetPotentialBestField();
	virtual void UnitAgent::FindAndSetNewGoal();
};
