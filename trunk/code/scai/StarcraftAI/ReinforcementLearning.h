#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include "Action.h"
class ReinforcementLearning
{
public:
	static struct Weights;
	static double ReinforcementLearning::CalculateTheta(double theta, double reward,double currQ, double nextQ, double force);
	static double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> squad);
	static void ReinforcementLearning::LoadWeightsFromFile();
	static void ReinforcementLearning::WriteValueToBuffer(double value, bool writeThrough); 
	static void ReinforcementLearning::SaveCurrentWeightsToFile();
	static void ReinforcementLearning::WriteRewardFile(double doubleToFile);
	static void ReinforcementLearning::WriteArrayToRewardFile(double doubleArray[]);
	static double ReinforcementLearning::GetForceAlly();
	static double ReinforcementLearning::GetForceSquad();
	static double ReinforcementLearning::GetForceMaxDist1();
	static double ReinforcementLearning::GetForceMaxDist2();
	static double ReinforcementLearning::GetForceCooldown();
	static double ReinforcementLearning::GetForceEdge();
	static void ReinforcementLearning::SetForceAlly(double ally);
	static void ReinforcementLearning::SetForceSquad(double squad);
	static void ReinforcementLearning::SetForceMaxDist1(double mde1);
	static void ReinforcementLearning::SetForceMaxDist2(double mde2);
	static void ReinforcementLearning::SetForceCooldown(double cool);
	static void ReinforcementLearning::SetForceEdge(double edge);
};
