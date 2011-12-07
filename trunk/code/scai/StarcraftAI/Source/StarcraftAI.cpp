#include "StarcraftAI.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../TacticsManager.h"
#include "../ScoutingManager.h"
#include "../ProductionManager.h"
#include "../WorkerManager.h"

using namespace BWAPI;
int gameCount = 1;
ReinforcementLearning reinforcementLearning = ReinforcementLearning();

struct StarcraftAI::Thetas
{
	double ally;
	double squad;
	double mde;
	double edge;
	double cool;
} _thetas; 


void StarcraftAI::onStart()
{
	remove( "C:/rewards.txt");
	StarcraftAI::reinforcementLearning.LoadWeightsFromFile();

	//BWAPI::Broodwar->sendText("war aint what it used to be");
	//BWAPI::Broodwar->sendText("black sheep wall");

	//Get the initial values of all the forces. 
	_thetas.ally = StarcraftAI::reinforcementLearning.GetForceAlly();
	_thetas.squad = StarcraftAI::reinforcementLearning.GetForceSquad();
	//BWAPI::Broodwar->printf("%f,%f :S:S:S",_thetas.squad,StarcraftAI::reinforcementLearning.GetForceSquad());
	_thetas.mde = StarcraftAI::reinforcementLearning.GetForceMaxDist();
	_thetas.edge = StarcraftAI::reinforcementLearning.GetForceEdge();
	_thetas.cool = StarcraftAI::reinforcementLearning.GetForceCooldown();

	Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);
	
	//scoutingManager.AnalyzeMap();
}

void StarcraftAI::onEnd(bool isWinner)
{	

	StarcraftAI::reinforcementLearning.SaveCurrentWeightsToFile(); 

	/*StarcraftAI::reinforcementLearning.WriteValueToBuffer(0,true);

	

	try
	{
		std::ifstream file("C:/rewards.txt"); 
		std::string line; 

		double edge, cool, mde, squad, ally; 
		double currQ; 
		double nextQ; 
		double reward; 
		
		for(int i = 0; std::getline(file,line); i++) 
		{
			if(i >= 8*5)
			{
				switch(i%8)
				{
					case 0:
						ally = atof(line.c_str());
						break; 
					case 1:
						squad = atof(line.c_str());
						break; 
					case 2:
						mde = atof(line.c_str());
						break;
					case 3:
						cool = atof(line.c_str());
						break; 
					case 4:
						edge = atof(line.c_str());
						break; 
					case 5:
						currQ = (-1)*atof(line.c_str());
						break; 
					case 6:
						nextQ = (-1)*atof(line.c_str());
						break; 
					case 7:
						reward = atof(line.c_str());
						_thetas.edge = ReinforcementLearning::CalculateTheta(_thetas.edge,reward,currQ,nextQ,edge);
						_thetas.cool = ReinforcementLearning::CalculateTheta(_thetas.cool,reward,currQ,nextQ,cool);
						_thetas.mde = ReinforcementLearning::CalculateTheta(_thetas.mde,reward,currQ,nextQ,mde);
						_thetas.squad = ReinforcementLearning::CalculateTheta(_thetas.squad,reward,currQ,nextQ,squad);
						_thetas.ally = ReinforcementLearning::CalculateTheta(_thetas.ally,reward,currQ,nextQ,ally);
						
						break;
					default:
						break; 
				}
			}
		}

		ReinforcementLearning::SetForceAlly(_thetas.ally);
		ReinforcementLearning::SetForceSquad(_thetas.squad);
		ReinforcementLearning::SetForceMaxDist(_thetas.mde);
		ReinforcementLearning::SetForceCooldown(_thetas.cool);
		ReinforcementLearning::SetForceEdge(_thetas.edge);
		ReinforcementLearning::SaveCurrentWeightsToFile(); 
		file.close(); 

	}
	catch(char *c)
	{
		BWAPI::Broodwar->printf("File could not be opened");
		std::cout << "File could not be opened -" << c << "\n";
	}*/
	gameCount++;
	BWAPI::Broodwar->restartGame();
}


void StarcraftAI::onFrame()
{
	
	TacticsManager::GetInstance()->Update();
	ScoutingManager::GetInstance()->Update();
	ProductionManager::GetInstance()->Update();
	WorkerManager::GetInstance()->Update();

	//TESTING:
	BWAPI::Broodwar->drawTextScreen(50,300,"Game Count is: = %d",gameCount);
	//TESTING:
	BWAPI::Broodwar->drawTextScreen(10,10,"Ally = %f",reinforcementLearning.GetForceAlly());
	BWAPI::Broodwar->drawTextScreen(10,20,"Edge = %f",reinforcementLearning.GetForceEdge());
	BWAPI::Broodwar->drawTextScreen(10,30,"MaxDist = %f",reinforcementLearning.GetForceMaxDist());
	BWAPI::Broodwar->drawTextScreen(10,40,"Squad = %f",reinforcementLearning.GetForceSquad());
	BWAPI::Broodwar->drawTextScreen(10,50,"Cooldown = %f",reinforcementLearning.GetForceCooldown());

	if(BWAPI::Broodwar->getFrameCount() % 25 == 0){
		
		double* liveBufferPointer = StarcraftAI::reinforcementLearning.GetLiveBuffer(); 
		int liveCount = StarcraftAI::reinforcementLearning.GetLiveCount(); 
		StarcraftAI::reinforcementLearning.ClearLiveBuffer(); 
	
		double edge, cool, mde, squad, ally; 
		double currQ; 
		double nextQ; 
		double reward; 

		for(int i=0; i<liveCount; i++){
			
			switch(i%8)
				{
				case 0:
					ally = liveBufferPointer[i];
					break; 
				case 1:
					squad = liveBufferPointer[i];
					//BWAPI::Broodwar->printf("%f - %f",squad,liveBufferPointer[i]);
					break; 
				case 2:
					mde = liveBufferPointer[i];;
					break;
				case 3:
					cool = liveBufferPointer[i];
					break; 
				case 4:
					edge = liveBufferPointer[i];
					break; 
				case 5:
					currQ = (-1)*liveBufferPointer[i];
					break; 
				case 6:
					nextQ = (-1)*liveBufferPointer[i];
					break; 
				case 7:
					reward = liveBufferPointer[i];

					_thetas.edge = ReinforcementLearning::CalculateTheta(_thetas.edge,reward,currQ,nextQ,edge);
					_thetas.cool = ReinforcementLearning::CalculateTheta(_thetas.cool,reward,currQ,nextQ,cool);
					_thetas.mde = ReinforcementLearning::CalculateTheta(_thetas.mde,reward,currQ,nextQ,mde);
					_thetas.squad = ReinforcementLearning::CalculateTheta(_thetas.squad,reward,currQ,nextQ,squad);
					_thetas.ally = ReinforcementLearning::CalculateTheta(_thetas.ally,reward,currQ,nextQ,ally);
					break;
				default:
					break; 
			}
		}
		std::ofstream file;
		file.open("C:/test.lgdat", std::ios::out | std::ios::app);
		file << _thetas.ally
			<< ";" << _thetas.squad
			<< ";"<< _thetas.mde
			<< ";"<< _thetas.cool 
			<< ";"<< _thetas.edge
			<< "\n";
		file.close();
	}
	ReinforcementLearning::SetForceAlly(_thetas.ally);
	ReinforcementLearning::SetForceSquad(_thetas.squad);
	ReinforcementLearning::SetForceMaxDist(_thetas.mde);
	ReinforcementLearning::SetForceCooldown(_thetas.cool);
	ReinforcementLearning::SetForceEdge(_thetas.edge);
	
}

void StarcraftAI::onSendText(std::string text)
{

}

void StarcraftAI::onReceiveText(BWAPI::Player* player, std::string text)
{
	
}

void StarcraftAI::onPlayerLeft(BWAPI::Player* player)
{
 
}

void StarcraftAI::onNukeDetect(BWAPI::Position target)
{

}

void StarcraftAI::onUnitDiscover(BWAPI::Unit* unit)
{
  
}

void StarcraftAI::onUnitEvade(BWAPI::Unit* unit)
{
  
}

void StarcraftAI::onUnitShow(BWAPI::Unit* unit)
{
	if(unit->getPlayer() == BWAPI::Broodwar->self())
	{
		//Assigns the units to the different managers
		//!!!! THE UNITS ARE ONLY BEING PRODUCED/CONSTRUCTED !!!!
		if(UnitHelper::IsOffensiveType(unit->getType()))
		{
			TacticsManager::GetInstance()->AssignToSquad(unit);
		}
		else if(unit->getType() == BWAPI::UnitTypes::Terran_SCV )
		{
			WorkerManager::GetInstance()->ScvCreated(unit);
		}
		else if(unit->getType().isBuilding() && (unit->getType().canProduce() || UnitHelper::CanResearch(unit)))
		{
			ProductionManager::GetInstance()->BuildingConstructed(unit);
		}
	}
}

void StarcraftAI::onUnitHide(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitCreate(BWAPI::Unit* unit)
{
}

void StarcraftAI::onUnitDestroy(BWAPI::Unit* unit)
{
	if(unit->getPlayer() == BWAPI::Broodwar->self())
	{
		//Assigns the units to the different managers
		if(UnitHelper::IsOffensiveType(unit->getType()))
		{
			TacticsManager::GetInstance()->UnitKilled(unit);
		}
		else if(unit->getType() == BWAPI::UnitTypes::Terran_SCV )
		{
			WorkerManager::GetInstance()->ScvKilled(unit);
		}
		else if(unit->getType().isBuilding() && unit->getType().canProduce())
		{
			ProductionManager::GetInstance()->BuildingDestroyed(unit);
		}
	}
}

void StarcraftAI::onUnitMorph(BWAPI::Unit* unit)
{

}

void StarcraftAI::onUnitRenegade(BWAPI::Unit* unit)
{

}

void StarcraftAI::onSaveGame(std::string gameName)
{

}


