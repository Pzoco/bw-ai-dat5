#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include "Action.h"
class ReinforcementLearning
{
public:
	static struct Weights;
	static double ReinforcementLearning::CalculateTheta(double theta, double reward,double currQ, double nextQ, double derivative);
	static double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> squad);
	static void ReinforcementLearning::LoadWeightsFromFile();
	static double* ReinforcementLearning::GetLiveBuffer(); 
	static int ReinforcementLearning::GetLiveCount(); 
	static void ReinforcementLearning::WriteLiveValue(double value); 
	static void ReinforcementLearning::ClearLiveBuffer();
	static void ReinforcementLearning::WriteValueToBuffer(double value, bool writeThrough); 
	static void ReinforcementLearning::SaveCurrentWeightsToFile();
	static void ReinforcementLearning::WriteRewardFile(double doubleToFile);
	static void ReinforcementLearning::WriteArrayToRewardFile(double doubleArray[]);
	static double ReinforcementLearning::GetForceAlly();
	static double ReinforcementLearning::GetForceSquad();
	static double ReinforcementLearning::GetForceMaxDist();
	static double ReinforcementLearning::GetForceCooldown();
	static double ReinforcementLearning::GetForceEdge();
	static void ReinforcementLearning::SetForceAlly(double ally);
	static void ReinforcementLearning::SetForceSquad(double squad);
	static void ReinforcementLearning::SetForceMaxDist(double mde1);
	static void ReinforcementLearning::SetForceCooldown(double cool);
	static void ReinforcementLearning::SetForceEdge(double edge);
};
