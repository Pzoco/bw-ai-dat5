#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class BaseTactic
{
public:
	BaseTactic();
	virtual struct Variables;
	virtual struct PotentialFieldParameters;
	virtual double BaseTactic::CalculateAllyPotential(BWAPI::Position);
	virtual double BaseTactic::CalculateEnemyPotential();
	virtual double BaseTactic::CalculateSquadCenterPotential(BWAPI::Position);
	virtual double BaseTactic::CalculateMaximumDistancePotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculateWeaponCoolDownPotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculateEdgesPotential();
	virtual double BaseTactic::CalculatePotentialField(BWAPI::Position);
	virtual void BaseTactic::InitializeParameters(PotentialFieldParameters &field,Variables &variables, std::set<BWAPI::Unit*> myUnits);
	virtual BWAPI::Position BaseTactic::GetPotentialBestField(double &currentGoalPotential, bool &allZero, std::set<BWAPI::Unit*> myUnits);
	virtual void BaseTactic::ExecuteTactic(BWAPI::Unit*,std::set<BWAPI::Unit*>);
	virtual Variables BaseTactic::GetVariables();
	virtual void BaseTactic::SetVariables(Variables vars);
};
