#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include "Action.h"
class ReinforcementLearning
{
public:
	struct Weights;
	double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> enemieUnits, std::set<BWAPI::Unit*> squad);
	void ReinforcementLearning::LoadWeightsFromFile();
	void ReinforcementLearning::SaveCurrentWeightsToFile();
	void ReinforcementLearning::UpdateCurrentWeights(double actualReward, double expectedReward);
	void ReinforcementLearning::OpenRewardFile();
	void ReinforcementLearning::CloseRewardFile();
	void ReinforcementLearning::WriteRewardFile(double doubleToFile);
	double ReinforcementLearning::UpdateWeight(double weight,double actualReward,double expectedReward);
};



