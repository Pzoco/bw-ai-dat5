#include "ReinforcementLearning.h"
#include "Action.h"
#include <iostream>
#include <algorithm>
#include <fstream>

struct Weights
{
	double FORCEALLY;
	double FORCESQUAD;
	double FORCEMAXDIST;
	double FORCECOOLDOWN;
	double FORCEEDGE;

}_weights;

double const alpha = 0.4;
double const gamma = 0.4;

//Manually change these when training
double const startingEnemies = 1;
double const startingEnemyMaxHealth = 1;
double const startingUnits = 1;
double const startingUnitMaxHealth = 1;
double const c1 = 1;
double const c2 = 1;
double const c3 = 1;
double const c4 = 1;

std::ofstream _file;
double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> enemieUnits, std::set<BWAPI::Unit*> squad)
{
	double reward = 0.0;
	double maxEnemieHealth = startingEnemies * startingEnemyMaxHealth;
	double maxUnitHealth = startingUnits * startingUnitMaxHealth;
	double enemyCurrentHealth = 0.0;
	double currentUnitHealth = 0.0;
	for(std::set<BWAPI::Unit*>::iterator j = enemieUnits.begin(); j != enemieUnits.end(); j++)
	{
		enemyCurrentHealth += (double)(*j)->getHitPoints();
	}
	for(std::set<BWAPI::Unit*>::iterator j = squad.begin(); j != squad.end(); j++)
	{
		currentUnitHealth += (double)(*j)->getHitPoints();
	}

	reward = c1 * squad.size() - c2 * (maxUnitHealth-currentUnitHealth) + c3 * (maxEnemieHealth-enemyCurrentHealth) + c4*(startingEnemies-enemieUnits.size());

	return reward;
}

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
		line.erase(0,strlen("FORCEALLY "));
		std::remove(line.begin(),line.end(),'\n');
		_weights.FORCEALLY = atof(line.c_str());
		
		//Gets the value of the edges theta
		std::getline(file,line);
		line.erase(0,strlen("FORCEEDGE "));
		std::remove(line.begin(),line.end(),'\n');
		_weights.FORCEEDGE = atof(line.c_str());
				
		//Gets the value of the MaximumDistance theta
		std::getline(file,line);
		line.erase(0,strlen("FORCEMAXDIST "));
		std::remove(line.begin(),line.end(),'\n');
		_weights.FORCEMAXDIST = atof(line.c_str());
				
		//Gets the value of the SquadCenter theta
		std::getline(file,line);
		line.erase(0,strlen("FORCESQUAD "));
		line.erase(std::remove(line.begin(),line.end(),'\n'));
		_weights.FORCESQUAD = atof(line.c_str());
		
		//Gets the value of the WeaponCoolDown theta
		std::getline(file,line);
		line.erase(0,strlen("FORCECOOLDOWN "));
		std::remove(line.begin(),line.end(),'\n');
		_weights.FORCECOOLDOWN = atof(line.c_str());
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
	file << "FORCEALLY "  << _weights.FORCEALLY <<"\n";
	file << "FORCEEDGE "<<_weights.FORCEEDGE<<"\n";
	file << "FORCEMAXDIST "<<_weights.FORCEMAXDIST<<"\n";
	file << "FORCESQUAD "<<_weights.FORCESQUAD <<"\n";
	file << "FORCECOOLDOWN "<<_weights.FORCECOOLDOWN<<"\n";
	file.close();
}
void ReinforcementLearning::OpenRewardFile()
{
	try
	{
		_file.open("rewards.txt");
		
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}
}
void ReinforcementLearning::CloseRewardFile()
{
	_file.close();
}
void ReinforcementLearning::WriteRewardFile(double doubleToFile)
{
	_file << doubleToFile <<"\n";
}

double ReinforcementLearning::UpdateWeight(double weight, double actualReward, double expectedReward)
{
	//Widrow-Hoff rule - is not finished dont know what to add
	return weight + alpha *(actualReward - expectedReward);
}

void ReinforcementLearning::UpdateCurrentWeights(double actualReward, double expectedReward)
{
	_weights.FORCEALLY = UpdateWeight(_weights.FORCEALLY,actualReward,expectedReward);
	_weights.FORCEEDGE = UpdateWeight(_weights.FORCEEDGE,actualReward,expectedReward);
	_weights.FORCEMAXDIST = UpdateWeight(_weights.FORCEMAXDIST,actualReward,expectedReward);
	_weights.FORCESQUAD = UpdateWeight(_weights.FORCESQUAD,actualReward,expectedReward);
	_weights.FORCECOOLDOWN = UpdateWeight(_weights.FORCECOOLDOWN,actualReward,expectedReward);
	
}








