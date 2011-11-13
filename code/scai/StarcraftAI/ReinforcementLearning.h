#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include "Action.h"
class ReinforcementLearning
{
public:
	void ReinforcementLearning::LoadWeightsFromFile();
	void ReinforcementLearning::SaveCurrentWeightsToFile();
	void ReinforcementLearning::UpdateCurrentWeights(Action action);
	double ReinforcementLearning::UpdateWeight(double weight,Action action);
};



