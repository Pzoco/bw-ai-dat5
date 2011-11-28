#include "ReinforcementLearning.h"
#include "Action.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>


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

//Manually change these when training______________
double const startingEnemies = 20;
double const startingEnemyMaxHealth = 40;
double const startingUnits = 5;
double const startingUnitMaxHealth = 80;
//_________________________________________________

//REWARD COEFICIENTS___________________
double const c1 = 200;
double const c2 = 1;
double const c3 = 2;
double const c4 = 100;
//_____________________________________

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
		//Making a list of the player's units
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

	try
	{
		std::ifstream file("C:/weights_data.txt"); 
		std::string line; 
		double arr[5]; 
		for(int i = 0; std::getline(file,line); i++) {
			arr[i] = atof(line.c_str()); 
			BWAPI::Broodwar->printf("=) %f", arr[i]); 
		}
		
		file.close(); 

		_weights.FORCEALLY = arr[0];
		_weights.FORCESQUAD = arr[1];
		_weights.FORCEMAXDIST = arr[2];
		_weights.FORCECOOLDOWN = arr[3];
		_weights.FORCEEDGE = arr[4];

	}
	catch(char *c)
	{
		BWAPI::Broodwar->printf("File could not be opened");
		std::cout << "File could not be opened -" << c << "\n";
	}

	//BWAPI::Broodwar->printf("Loaded = %f,%f,%f,%f,%f",(double)_weights.FORCEALLY,(double)_weights.FORCEEDGE,(double)_weights.FORCEMAXDIST,(double)_weights.FORCESQUAD,(double)_weights.FORCECOOLDOWN);
	
}
void ReinforcementLearning::SaveCurrentWeightsToFile()
{
	std::ofstream file;
	try
	{
		file.open("C:/weights_data.txt");
		file << _weights.FORCEALLY <<"\n";
		file <<_weights.FORCEEDGE<<"\n";
		file <<_weights.FORCEMAXDIST<<"\n";
		file <<_weights.FORCESQUAD <<"\n";
		file <<_weights.FORCECOOLDOWN<<"\n";
		file.close();
		
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}

}

void ReinforcementLearning::WriteRewardFile(double doubleToFile)
{	
	
	std::ofstream file; 
	try
	{
		file.open("C:/rewards.txt", std::ios::out | std::ios::app);
		file << doubleToFile << "\n";
		file.close();
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}
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

double ReinforcementLearning::GetForceAlly(){
	return _weights.FORCEALLY; 
}

double ReinforcementLearning::GetForceSquad(){
	return _weights.FORCESQUAD; 
}

double ReinforcementLearning::GetForceMaxDist(){
	return _weights.FORCEMAXDIST; 
}

double ReinforcementLearning::GetForceCooldown(){
	return _weights.FORCECOOLDOWN; 
}

double ReinforcementLearning::GetForceEdge(){
	return _weights.FORCEEDGE;
}



