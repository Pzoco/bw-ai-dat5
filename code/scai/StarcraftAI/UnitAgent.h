#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class UnitAgent
{
public:
	UnitAgent();
	UnitAgent(BWAPI::Unit* unit);
	virtual struct PotentialFieldParameters;
	virtual double UnitAgent::CalculateAllyPotential(BWAPI::Position);
	virtual double UnitAgent::CalculateEnemyPotential();
	virtual double UnitAgent::CalculateSquadCenterPotential(BWAPI::Position);
	virtual double UnitAgent::CalculateMaximumDistancePotential();
	virtual double UnitAgent::CalculateWeaponCoolDownPotential();
	virtual double UnitAgent::CalculateEdgesPotential();
	virtual double UnitAgent::CalculatePotentialField(BWAPI::Position);
	virtual void UnitAgent::InitializeParameters(PotentialFieldParameters &field);
	virtual BWAPI::Position UnitAgent::GetPotentialBestField(double &currentGoalPotential, bool &allZero);
	virtual BWAPI::Unit* UnitAgent::GetUnit();
	virtual void UnitAgent::FindAndSetNewGoal();
};
