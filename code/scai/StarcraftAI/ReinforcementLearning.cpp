#include "ReinforcementLearning.h"
#include "Weights.h"
#include "Action.h"
#include <iostream>
#include <algorithm>
#include <fstream>

Weights currentWeights;
double const alpha = 0.4;

void ReinforcementLearning::LoadWeightsFromFile()
{
	std::ifstream file;
	try
	{
		file.open("weights_data.txt");
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}
	try
	{
		std::string line;
		//Gets the value of the ally theta:
		std::getline(file,line);
		line.erase(0,strlen("Ally "));
		std::remove(line.begin(),line.end(),'\n');
		currentWeights.thetaAllyPF = atof(line.c_str());
		
		//Gets the value of the edges theta
		std::getline(file,line);
		line.erase(0,strlen("Edges "));
		std::remove(line.begin(),line.end(),'\n');
		currentWeights.thetaAllyPF = atof(line.c_str());
				
		//Gets the value of the MaximumDistance theta
		std::getline(file,line);
		line.erase(0,strlen("MaximumDistance "));
		std::remove(line.begin(),line.end(),'\n');
		currentWeights.thetaAllyPF = atof(line.c_str());
				
		//Gets the value of the SquadCenter theta
		std::getline(file,line);
		line.erase(0,strlen("SquadCenter "));
		line.erase(std::remove(line.begin(),line.end(),'\n'));
		currentWeights.thetaAllyPF = atof(line.c_str());
		
		//Gets the value of the WeaponCoolDown theta
		std::getline(file,line);
		line.erase(0,strlen("WeaponCoolDown "));
		std::remove(line.begin(),line.end(),'\n');
		currentWeights.thetaAllyPF = atof(line.c_str());
	}
	catch(char *c)
	{
		std::cout << "Wrong format of file -" << c << "\n";
	}
	
	
}
void ReinforcementLearning::SaveCurrentWeightsToFile()
{
	std::ofstream file;
	try
	{
		file.open("weights_data.txt");
		
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}
	file << "Ally "  << currentWeights.thetaAllyPF <<"\n";
	file << "Edges "<<currentWeights.thetaEdgesPF<<"\n";
	file << "MaximumDistance "<<currentWeights.thetaMaximumDistancePF<<"\n";
	file << "SquadCenter "<<currentWeights.thetaSquadCenterPF <<"\n";
	file << "WeaponCoolDown "<<currentWeights.thetaWeaponCoolDownPF<<"\n";
	file.close();
}
void ReinforcementLearning::UpdateCurrentWeights(Action action)
{
	currentWeights.thetaAllyPF = UpdateWeight(currentWeights.thetaAllyPF,action);
	currentWeights.thetaEdgesPF = UpdateWeight(currentWeights.thetaEdgesPF,action);
	currentWeights.thetaMaximumDistancePF = UpdateWeight(currentWeights.thetaMaximumDistancePF,action);
	currentWeights.thetaSquadCenterPF = UpdateWeight(currentWeights.thetaSquadCenterPF,action);
	currentWeights.thetaWeaponCoolDownPF = UpdateWeight(currentWeights.thetaWeaponCoolDownPF,action);
	
}
double ReinforcementLearning::UpdateWeight(double weight, Action action)
{
	//Widrow-Hoff rule - is not finished dont know what to add
	return weight + alpha *(action.actualReward - action.expectedReward);
}







