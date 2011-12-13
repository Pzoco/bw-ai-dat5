#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include "Action.h"
class ReinforcementLearning
{
public:
	
	//Actual reinforcement learning
	static double ReinforcementLearning::CalculateTheta(double theta, double reward,double currQ, double nextQ, double derivative);
	static double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> squad);

	//Load/Save weights
	static struct Weights;
	static void ReinforcementLearning::LoadWeightsFromFile();
	static void ReinforcementLearning::SaveCurrentWeightsToFile();

	//Buffer
	static double* ReinforcementLearning::GetLiveBuffer(); 
	static int ReinforcementLearning::GetLiveCount(); 
	static void ReinforcementLearning::WriteLiveValue(double value); 
	static void ReinforcementLearning::ClearLiveBuffer();

	//Getters and setters
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

	//Gamedata
	static void ReinforcementLearning::WriteToDataFiles();
};
