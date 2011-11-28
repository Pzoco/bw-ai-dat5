#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include "Action.h"
class ReinforcementLearning
{
public:
	static struct Weights;
	static double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> squad);
	static void ReinforcementLearning::LoadWeightsFromFile();
	static void ReinforcementLearning::SaveCurrentWeightsToFile();
	static void ReinforcementLearning::UpdateCurrentWeights(double actualReward, double expectedReward);
	static void ReinforcementLearning::WriteRewardFile(double doubleToFile);
	static double ReinforcementLearning::UpdateWeight(double weight,double actualReward,double expectedReward);
	static double ReinforcementLearning::GetForceAlly();
	static double ReinforcementLearning::GetForceSquad();
	static double ReinforcementLearning::GetForceMaxDist();
	static double ReinforcementLearning::GetForceCooldown();
	static double ReinforcementLearning::GetForceEdge();

};
