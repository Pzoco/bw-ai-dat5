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
	double FORCEMAXDIST1;
	double FORCEMAXDIST2;
	double FORCECOOLDOWN;
	double FORCEEDGE;

}_weights;

double const alpha = 0.5;
double const gamma = 0.5;

//Manually change these when training______________
double const startingEnemies = 20;
double const startingEnemyMaxHealth = 40;
double const startingUnits = 5;
double const startingUnitMaxHealth = 80;
//_________________________________________________

//REWARD COEFICIENTS___________________
double const c1 = -180;	//Our units		-180 (startingUnitMaxHealth*2+20) for dying, 20 is because we care more about us then them
double const c2 = -1;	//Our health	-1 for damage taken
double const c3 = 1;	//There health	1 for damage
double const c4 = 40;	//There units	40 (startingEnemies * 2) for killing
double const c5 = -5;	//adjustment	-5 for doing nothing
//_____________________________________

double ReinforcementLearning::CalculateTheta(double theta, double reward,double currQ, double nextQ, double derivative)
{
	/*std::ofstream file;
	double test = theta + alpha * (reward + gamma * nextQ - currQ) * derivative;
	file.open("C:/test.txt", std::ios::out | std::ios::app);
	file << test << ", " << theta << ", " << alpha << ", " << reward << ", " << gamma << ", " << nextQ << ", " << currQ << ", " << derivative << "\n";
	file.close();*/
	return theta + alpha * (reward + gamma * nextQ - currQ) * derivative; 
}

double ReinforcementLearning::CalculateReward(std::set<BWAPI::Unit*> squad)
{
	double reward = 0.0;
	double maxEnemieHealth = startingEnemies * startingEnemyMaxHealth;
	double maxUnitHealth = startingUnits * startingUnitMaxHealth;
	double enemyCurrentHealth = 0.0;
	double currentUnitHealth = 0.0;
	double numberOfEnemies = 0.0;
	double squadSize = 0.0;

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
			numberOfEnemies++;
			//BWAPI::Broodwar->printf("enemy in range");
		}
	}
	for(std::set<BWAPI::Unit*>::iterator j = squad.begin(); j != squad.end(); j++)
	{
		if((*j)->exists())
		{
			squadSize++;
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

	reward = c1 * (startingUnits - squadSize) + c2 * (maxUnitHealth-currentUnitHealth) + c3 * (maxEnemieHealth-enemyCurrentHealth) + c4*(startingEnemies-numberOfEnemies)+ c5;
	BWAPI::Broodwar->drawTextScreen(10,80,"size = %f",c1 * (startingUnits - squadSize));
	BWAPI::Broodwar->drawTextScreen(10,90,"health = %f",c2*(maxUnitHealth-currentUnitHealth));
	BWAPI::Broodwar->drawTextScreen(10,100,"ehealth = %f",c3*(maxEnemieHealth-enemyCurrentHealth));
	BWAPI::Broodwar->drawTextScreen(10,110,"esize = %f",c4*(startingEnemies-numberOfEnemies));
	BWAPI::Broodwar->drawTextScreen(10,120,"reward = %f",reward);
	return reward;
}

void ReinforcementLearning::LoadWeightsFromFile()
{

	try
	{
		std::ifstream file("C:/weights_data.txt"); 
		std::string line; 
		double arr[6]; 
		for(int i = 0; std::getline(file,line); i++) {
			arr[i] = atof(line.c_str()); 
			//BWAPI::Broodwar->printf("=) %f", arr[i]); 
		}
		
		file.close(); 

		_weights.FORCEALLY = arr[0];
		_weights.FORCESQUAD = arr[1];
		_weights.FORCEMAXDIST1 = arr[2];
		_weights.FORCEMAXDIST2 = arr[3];
		_weights.FORCECOOLDOWN = arr[4];
		_weights.FORCEEDGE = arr[5];

	}
	catch(char *c)
	{
		BWAPI::Broodwar->printf("File could not be opened");
		std::cout << "File could not be opened -" << c << "\n";
	}
	
	//BWAPI::Broodwar->printf("Loaded = %f,%f,%f,%f,%f,%f",(double)_weights.FORCEALLY,(double)_weights.FORCEEDGE,(double)_weights.FORCEMAXDIST1,(double)_weights.FORCEMAXDIST2,(double)_weights.FORCESQUAD,(double)_weights.FORCECOOLDOWN);
	
}





double fileBuffer[130000]; 
int bufferCounter = 0;


void ReinforcementLearning::WriteValueToBuffer(double value, bool writeThrough)
{
	if(bufferCounter == 130000)
	{
		std::ofstream file;
		file.open("C:/rewards.txt", std::ios::out | std::ios::app);
		
		for(int i = 0; i < bufferCounter; i++)
		{
			file << fileBuffer[i] << "\n";
		}
		
		file.close();
		bufferCounter = 0;
	}else if(writeThrough)
	{
		std::ofstream file;
		file.open("C:/rewards.txt", std::ios::out | std::ios::app);
		
		for(int i = 0; i <bufferCounter; i++)
		{
			file << fileBuffer[i] << "\n";
		}
		
		file.close();
		bufferCounter = 0; 

	}else
	{
		fileBuffer[bufferCounter++] = value; 
	}
}

void ReinforcementLearning::SaveCurrentWeightsToFile()
{
	std::ofstream file;
	try
	{
		file.open("C:/weights_data.txt");
		file << _weights.FORCEALLY <<"\n";
		file <<_weights.FORCESQUAD <<"\n";
		file <<_weights.FORCEMAXDIST1<<"\n";
		file <<_weights.FORCEMAXDIST2<<"\n";
		file <<_weights.FORCECOOLDOWN<<"\n";
		file <<_weights.FORCEEDGE<<"\n";
		
		
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

void ReinforcementLearning::WriteArrayToRewardFile(double doubleArray[])
{	
	std::ofstream file; 
	try
	{
		file.open("C:/rewards.txt", std::ios::out | std::ios::app);
		for(int i = 0; i < sizeof(doubleArray); i++)
		{
			file << doubleArray[i] << "\n";
		}
		file.close();
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}
}





double ReinforcementLearning::GetForceAlly(){
	return _weights.FORCEALLY; 
}

double ReinforcementLearning::GetForceSquad(){
	return _weights.FORCESQUAD; 
}

double ReinforcementLearning::GetForceMaxDist1(){
	return _weights.FORCEMAXDIST1; 
}
double ReinforcementLearning::GetForceMaxDist2(){
	return _weights.FORCEMAXDIST2; 
}

double ReinforcementLearning::GetForceCooldown(){
	return _weights.FORCECOOLDOWN; 
}

double ReinforcementLearning::GetForceEdge(){
	return _weights.FORCEEDGE;
}

void ReinforcementLearning::SetForceAlly(double ally){
	_weights.FORCEALLY = ally; 
}

void ReinforcementLearning::SetForceSquad(double squad){
	_weights.FORCESQUAD = squad;  
}

void ReinforcementLearning::SetForceMaxDist1(double mde1){
	_weights.FORCEMAXDIST1 = mde1; 
}

void ReinforcementLearning::SetForceMaxDist2(double mde2){
	_weights.FORCEMAXDIST2 = mde2; 
}

void ReinforcementLearning::SetForceCooldown(double cool){
	_weights.FORCECOOLDOWN = cool; 
}

void ReinforcementLearning::SetForceEdge(double edge){
	_weights.FORCEEDGE = edge;
}

