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
	virtual double BaseTactic::CalculateSquadCenterPotential(BWAPI::Position);
	virtual double BaseTactic::CalculateMaximumDistancePotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculateWeaponCoolDownPotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculateEdgesPotential(BWAPI::Position pos);
	virtual double BaseTactic::CalculatePotentialField(BWAPI::Position pos);
	virtual void BaseTactic::InitializeParameters(std::set<BWAPI::Unit*> myUnits);
	virtual void BaseTactic::InitializeQParameters(std::set<BWAPI::Unit*> myUnits,BWAPI::Position fakeUnitPos);
	virtual double BaseTactic::CalculateQPotentialField(BWAPI::Position pos,BWAPI::Position fakeUnitPos);
	virtual double BaseTactic::CalculateBestQPotentialField(BWAPI::Position fakeUnitPos);
	virtual BWAPI::Position BaseTactic::GetBestPositionBasedOnPotential(std::set<BWAPI::Unit*> myUnits);
	double BaseTactic::CalculateQ();
	virtual void BaseTactic::ExecuteTactic(BWAPI::Unit*,std::set<BWAPI::Unit*>);
	virtual Variables BaseTactic::GetVariables();
	virtual void BaseTactic::SetVariables(Variables vars);
};
