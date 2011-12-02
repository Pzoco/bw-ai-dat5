#include "StarcraftAI.h"
#include "../Squad.h"
#include "../UnitHelper.h"
#include "../BaseTactic.h"
#include "../TacticsManager.h"
#include "../ScoutingManager.h"
#include "../ProductionManager.h"
#include "../ReinforcementLearning.h"
#include "../WorkerManager.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace BWAPI;
TacticsManager tacticsManager;
ScoutingManager scoutingManager;
ProductionManager productionManager;
WorkerManager workerManager;

ReinforcementLearning reinforcementLearning = ReinforcementLearning();

struct StarcraftAI::Thetas
{
	double ally;
	double squad;
	double mde1;
	double mde2;
	double edge;
	double cool;
} _thetas; 


void StarcraftAI::onStart()
{
	remove( "C:/rewards.txt");


	StarcraftAI::reinforcementLearning.LoadWeightsFromFile();

	//Get the initial values of all the forces. 
	_thetas.ally = StarcraftAI::reinforcementLearning.GetForceAlly();
	_thetas.squad = StarcraftAI::reinforcementLearning.GetForceSquad();
	_thetas.mde1 = StarcraftAI::reinforcementLearning.GetForceMaxDist1();
	_thetas.mde2 = StarcraftAI::reinforcementLearning.GetForceMaxDist2();
	_thetas.edge = StarcraftAI::reinforcementLearning.GetForceEdge();
	_thetas.cool = StarcraftAI::reinforcementLearning.GetForceCooldown();

	Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);

	//Iniatiating managers:
	tacticsManager = TacticsManager();
	scoutingManager = ScoutingManager();
	productionManager = ProductionManager();
	workerManager = WorkerManager();

	//This makes it look like it crashed if the map was exited before it is done analyzing
	//scoutingManager.AnalyzeMap();
}

void StarcraftAI::onEnd(bool isWinner)
{	
	StarcraftAI::reinforcementLearning.WriteValueToBuffer(0,true);

	StarcraftAI::reinforcementLearning.SaveCurrentWeightsToFile(); 

	try
	{
		std::ifstream file("C:/rewards.txt"); 
		std::string line; 

		double edge, cool, mde1, mde2, squad, ally; 
		double currQ; 
		double nextQ; 
		double reward; 
		
		for(int i = 0; std::getline(file,line); i++) 
		{
			switch(i%9)
			{
				case 0:
					ally = atof(line.c_str());
					break; 
				case 1:
					squad = atof(line.c_str());
					break; 
				case 2:
					mde1 = atof(line.c_str());
					break;
				case 3:
					mde2 = atof(line.c_str());
					break; 
				case 4:
					cool = atof(line.c_str());
					break; 
				case 5:
					edge = atof(line.c_str());
					break; 
				case 6:
					currQ = (-1)*atof(line.c_str());
					break; 
				case 7:
					nextQ = (-1)*atof(line.c_str());
					break; 
				case 8:
					reward = atof(line.c_str());
					_thetas.edge = ReinforcementLearning::CalculateTheta(_thetas.edge,reward,currQ,nextQ,edge);
					_thetas.cool = ReinforcementLearning::CalculateTheta(_thetas.cool,reward,currQ,nextQ,cool);
					_thetas.mde1 = ReinforcementLearning::CalculateTheta(_thetas.mde1,reward,currQ,nextQ,mde1);
					_thetas.mde2 = ReinforcementLearning::CalculateTheta(_thetas.mde2,reward,currQ,nextQ,mde2);
					_thetas.squad = ReinforcementLearning::CalculateTheta(_thetas.squad,reward,currQ,nextQ,squad);
					_thetas.ally = ReinforcementLearning::CalculateTheta(_thetas.ally,reward,currQ,nextQ,ally);
					
					break;
				default:
					break; 
			}
		}

		ReinforcementLearning::SetForceAlly(_thetas.ally);
		ReinforcementLearning::SetForceSquad(_thetas.squad);
		ReinforcementLearning::SetForceMaxDist1(_thetas.mde1);
		ReinforcementLearning::SetForceMaxDist2(_thetas.mde2);
		ReinforcementLearning::SetForceCooldown(_thetas.cool);
		ReinforcementLearning::SetForceEdge(_thetas.edge);
		ReinforcementLearning::SaveCurrentWeightsToFile(); 
		file.close(); 

	}
	catch(char *c)
	{
		BWAPI::Broodwar->printf("File could not be opened");
		std::cout << "File could not be opened -" << c << "\n";
	}
}

void StarcraftAI::onFrame()
{
	tacticsManager.Update();
	scoutingManager.Update();
	productionManager.Update();
	workerManager.Update();

	BWAPI::Broodwar->drawTextScreen(10,10,"Ally = %f",reinforcementLearning.GetForceAlly());
	BWAPI::Broodwar->drawTextScreen(10,20,"Edge = %f",reinforcementLearning.GetForceEdge());
	BWAPI::Broodwar->drawTextScreen(10,30,"MaxDist1 = %f",reinforcementLearning.GetForceMaxDist1());
	BWAPI::Broodwar->drawTextScreen(10,40,"MaxDist1 = %f",reinforcementLearning.GetForceMaxDist2());
	BWAPI::Broodwar->drawTextScreen(10,50,"Squad = %f",reinforcementLearning.GetForceSquad());
	BWAPI::Broodwar->drawTextScreen(10,60,"Cooldown = %f",reinforcementLearning.GetForceCooldown());
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
			tacticsManager.AssignToSquad(unit);
		}
		else if(unit->getType() == BWAPI::UnitTypes::Terran_SCV )
		{
			workerManager.ScvCreated(unit);
		}
		else if(unit->getType().isBuilding())
		{
			productionManager.BuildingConstructed(unit);
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


