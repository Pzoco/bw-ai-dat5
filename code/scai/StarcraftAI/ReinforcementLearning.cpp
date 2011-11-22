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
double const startingEnemies = 20;
double const startingEnemyMaxHealth = 40;
double const startingUnits = 5;
double const startingUnitMaxHealth = 80;
double const c1 = 100;
double const c2 = 1;
double const c3 = 0.5;
double const c4 = 1.125;

std::ofstream _file;
double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> squad)
{
	double reward = 0.0;
	double maxEnemieHealth = startingEnemies * startingEnemyMaxHealth;
	double maxUnitHealth = startingUnits * startingUnitMaxHealth;
	double enemyCurrentHealth = 0.0;
	double currentUnitHealth = 0.0;
	std::set<BWAPI::Player*> enemies = BWAPI::Broodwar->enemies();	
	std::set<BWAPI::Unit*> enemieUnits;
	for(std::set<BWAPI::Player*>::const_iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		//Making a list of that players units
		std::set<BWAPI::Unit*> tempUnits = (*i)->getUnits();

		//Iterating trough them.
		for(std::set<BWAPI::Unit*>::iterator j = tempUnits.begin(); j != tempUnits.end(); j++)
		{
			//And add them to a list of all enemieunits in the map.
			enemieUnits.insert((*j));
			//BWAPI::Broodwar->printf("enemy in range");
		}
	}
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
		file.open("C:/weights_data.txt");
		BWAPI::Broodwar->printf("WEIGHTS FILE - OPEN"); 
	}
	catch(char *c)
	{
		BWAPI::Broodwar->printf("File could not be opened");
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
	BWAPI::Broodwar->printf("Loaded = %d,%d,%d,%d,%d",(double)_weights.FORCEALLY,(double)_weights.FORCEEDGE,(double)_weights.FORCEMAXDIST,(double)_weights.FORCESQUAD,(double)_weights.FORCECOOLDOWN);
	
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




