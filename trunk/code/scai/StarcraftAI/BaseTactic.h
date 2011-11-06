#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class BaseTactic
{
public:
	BaseTactic();
	virtual struct Constants;
	virtual struct PotentialFieldParameters;
	virtual double BaseTactic::CalculateAllyPotential(BWAPI::Position);
	virtual double BaseTactic::CalculateEnemyPotential();
	virtual double BaseTactic::CalculateSquadCenterPotential(BWAPI::Position);
	virtual double BaseTactic::CalculateMaximumDistancePotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculateWeaponCoolDownPotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculateEdgesPotential();
	virtual double BaseTactic::CalculatePotentialField(BWAPI::Position);
	virtual void BaseTactic::InitializeParameters(PotentialFieldParameters &field,Constants &constants);
	virtual BWAPI::Position BaseTactic::GetPotentialBestField(double &currentGoalPotential, bool &allZero);
	virtual void BaseTactic::ExecuteTactic(BWAPI::Unit*);
	virtual Constants BaseTactic::GetConstants();
	virtual void BaseTactic::SetConstants(Constants cons);
};
