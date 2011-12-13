#pragma once
#include <BWAPI.h>
#include <BWTA.h>

class BaseTactic
{
public:
	BaseTactic();
	virtual struct Variables;
	virtual struct PotentialFieldParameters;
	virtual double BaseTactic::CalculateQPotentialField(BWAPI::Position pos, bool print);
	virtual void BaseTactic::InitializeParameters(std::set<BWAPI::Unit*> myUnits);
	virtual BWAPI::Position BaseTactic::GetBestPositionBasedOnPotential(std::set<BWAPI::Unit*> myUnits);
	double BaseTactic::CalculateQ();
	virtual void BaseTactic::ExecuteTactic(BWAPI::Unit*,std::set<BWAPI::Unit*>);
	virtual Variables BaseTactic::GetVariables();
	virtual void BaseTactic::SetVariables(Variables vars);
};
