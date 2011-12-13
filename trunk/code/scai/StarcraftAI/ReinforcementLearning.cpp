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

double const alpha = 0.2;
double const gamma = 0.9;
//Manually change these when training______________
double const startingEnemies = 10;
double const startingEnemyMaxHealth = 40;
double const startingUnits = 5;
double const startingUnitMaxHealth = 80;
//_________________________________________________

//REWARD COEFICIENTS___________________
double const c1 = -180;	//Our units		-180 (startingUnitMaxHealth*2+20) for dying, 20 is because we care more about us then them
double const c2 = -1;	//Our health	-1 for damage taken
double const c3 = 2;	//Their health   2 for damage
double const c4 = 40;	//Their units	40 (startingEnemies * 2) for killing
double const c5 = -0.025;	//Time
//_____________________________________

/*
	The following functions is handling the reinforcement learning
*/
double ReinforcementLearning::CalculateTheta(double theta, double reward,double currQ, double nextQ, double derivative)
{
	//Calculating the updating rule. This calculation is from the book!
	double newtheta = theta + alpha * (reward + gamma * nextQ - currQ) * derivative;
	return newtheta;
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


	reward = c1 * (startingUnits - squadSize) + c2 * (maxUnitHealth-currentUnitHealth) + c3 * (maxEnemieHealth-enemyCurrentHealth) + c4*(startingEnemies-numberOfEnemies)+ c5*(BWAPI::Broodwar->getFrameCount());
	double reward2 = reward / 1000;

	/*
		Writing to the screen for awesomeness
	*/
	BWAPI::Broodwar->drawTextScreen(10,80,"Units Killed = %f",(startingUnits - squadSize));
	BWAPI::Broodwar->drawTextScreen(10,90,"Damage Taken= %f",(maxUnitHealth-currentUnitHealth));
	BWAPI::Broodwar->drawTextScreen(10,100,"Damage Given = %f",(maxEnemieHealth-enemyCurrentHealth));
	BWAPI::Broodwar->drawTextScreen(10,110,"Enemies Killed = %f",(startingEnemies-numberOfEnemies));
	BWAPI::Broodwar->drawTextScreen(10,120,"Current Reward = %f",reward2);

	return reward2;
}
/*
	The following functions is handling the loading and saving the weights.
	
*/

void ReinforcementLearning::LoadWeightsFromFile()
{

	try
	{
		std::ifstream file("C:/weights_data.txt"); 
		std::string line; 
		double arr[5]; 
		for(int i = 0; std::getline(file,line); i++) {
			arr[i] = atof(line.c_str()); 
			//BWAPI::Broodwar->printf("=) %f", arr[i]); 
		}
		
		file.close(); 

		_weights.FORCEALLY = arr[0];
		_weights.FORCESQUAD = arr[1];
		//BWAPI::Broodwar->printf("=) %f, %f",_weights.FORCESQUAD , arr[1]); 
		_weights.FORCEMAXDIST = arr[2];
		_weights.FORCECOOLDOWN = arr[3];
		_weights.FORCEEDGE = arr[4];

	}
	catch(char *c)
	{
		BWAPI::Broodwar->printf("File could not be opened");
		std::cout << "File could not be opened -" << c << "\n";
	}
}
void ReinforcementLearning::SaveCurrentWeightsToFile()
{
	//Saveing to weights to a file
	std::ofstream file;
	try
	{
		file.open("C:/weights_data.txt");
		file << _weights.FORCEALLY <<"\n";
		file <<_weights.FORCESQUAD <<"\n";
		file <<_weights.FORCEMAXDIST<<"\n";
		file <<_weights.FORCECOOLDOWN<<"\n";
		file <<_weights.FORCEEDGE<<"\n";
		
		
		file.close();
		
	}
	catch(char *c)
	{
		std::cout << "File could not be opened -" << c << "\n";
	}

	//FOR SAVING NUMBER OF ENEMIES KILLED
	double numberOfEnemies = 0.0;
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
	std::ofstream file2; 
	try
	{
		file2.open("C:/kills.lgdat", std::ios::out | std::ios::app);
		file2 << (startingEnemies-numberOfEnemies) << "\n";
		file2.close();
	}
	catch(char *c)
	{
		
	}

}


/*
	The following functions is handling the buffer.
	If we dont use a buffer the IO will make the game to slow!
*/

double liveBuffer[10000];
int liveCount = 0; 

double* ReinforcementLearning::GetLiveBuffer()
{
	return liveBuffer; 
}

int ReinforcementLearning::GetLiveCount()
{
	return liveCount;
}


void ReinforcementLearning::WriteLiveValue(double value)
{
	liveBuffer[liveCount++] = value; 

}

void ReinforcementLearning::ClearLiveBuffer()
{
	//Make this cleanear later
	liveCount = 0; 

}

/*
	The following functions is getters and setters for all the forces.
*/
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

void ReinforcementLearning::SetForceAlly(double ally){
	_weights.FORCEALLY = ally; 
}

void ReinforcementLearning::SetForceSquad(double squad){
	_weights.FORCESQUAD = squad;  
}

void ReinforcementLearning::SetForceMaxDist(double mde1){
	_weights.FORCEMAXDIST = mde1; 
}


void ReinforcementLearning::SetForceCooldown(double cool){
	_weights.FORCECOOLDOWN = cool; 
}

void ReinforcementLearning::SetForceEdge(double edge){
	_weights.FORCEEDGE = edge;
}
/*
	WriteToDataFiles is used only for statictics. We basically do the same thing as in the reward part, 
	but we save it at the end of the game to get the final stats for comparisons.
*/
void ReinforcementLearning::WriteToDataFiles()
{
	double reward = 0.0;
	double maxEnemieHealth = startingEnemies * startingEnemyMaxHealth;
	double maxUnitHealth = startingUnits * startingUnitMaxHealth;
	double enemyCurrentHealth = 0.0;
	double currentUnitHealth = 0.0;
	double numberOfEnemies = 0.0;
	double squadSize = 0.0;

	//Calculate current number of enemies
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

	//Calculate current squad sieze
	std::set<BWAPI::Unit*> squad = BWAPI::Broodwar->getAllUnits();
	for(std::set<BWAPI::Unit*>::iterator j = squad.begin(); j != squad.end(); j++)
	{
		if((*j)->exists() && ((*j)->getType() == BWAPI::UnitTypes::Terran_Vulture))
		{
			squadSize++;
		}
	}

	//Calculate current hp for enemy
	for(std::set<BWAPI::Unit*>::iterator j = enemieUnits.begin(); j != enemieUnits.end(); j++)
	{
		enemyCurrentHealth += (double)(*j)->getHitPoints();
	}
	
	//Calculate current hp
	for(std::set<BWAPI::Unit*>::iterator j = squad.begin(); j != squad.end(); j++)
	{
		if((*j)->exists() && ((*j)->getType() == BWAPI::UnitTypes::Terran_Vulture))
		{
			currentUnitHealth += (double)(*j)->getHitPoints();
		}
	}


	//Getting the game count
	std::ifstream countin("C:/gameCount.txt");
	std::string line;
	std::getline(countin,line);
	int gameCount = atoi(line.c_str());
	countin.close();


	//Writing to file
	std::ofstream gameData;
	std::ofstream gameData2;

	gameData.open("C:/gameData.lgdat", std::ios::out | std::ios::app);
	gameData2.open("C:/gameData2.lgdat", std::ios::out | std::ios::app);
	gameData
		<< (maxUnitHealth-currentUnitHealth) << "; "
		<< (maxEnemieHealth-enemyCurrentHealth) << "; "
		<< "\n";
	gameData2
		<< (startingUnits - squadSize) << "; "
		<< (startingEnemies-numberOfEnemies) << "; "
		<< "\n";

	gameData.close();
	gameData2.close();
	
}