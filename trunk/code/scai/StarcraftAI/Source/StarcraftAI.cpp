#include "StarcraftAI.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <iostream>
#include <fstream>
#include <string>
#include "hugin"
#include "../TacticsManager.h"
#include "../ScoutingManager.h"
#include "../ProductionManager.h"
#include "../WorkerManager.h"
#include "../StrategyManager.h"


#include "math.h"


using namespace BWAPI;
using namespace HAPI;
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


bool containsUtilities (const NodeList& list)
{
    for (size_t i = 0, n = list.size(); i < n; i++)
	if (list[i]->getCategory() == H_CATEGORY_UTILITY)
	    return true;

    return false;
}

void StarcraftAI::onStart()
{
	

	//Printing network
	HAPI::NodeList nodes = domain.getNodes();

	bool hasUtilities = containsUtilities (nodes);

	for (HAPI::NodeList::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
		HAPI::Node *node = *it;
		//BWAPI::Broodwar->printf("%s",node->getName().c_str());
		
		
		Category category = node->getCategory();
		char type = (category == H_CATEGORY_CHANCE ? 'C'
				 : category == H_CATEGORY_DECISION ? 'D'
				 : category == H_CATEGORY_UTILITY ? 'U' : 'F');

		BWAPI::Broodwar->printf("[%c] %s",type,node->getName().c_str());


		if (category == H_CATEGORY_UTILITY)
		{ 
			UtilityNode *uNode = dynamic_cast<UtilityNode*> (node);
			std::cout << "  - Expected utility: " << uNode->getExpectedUtility() << std::endl;
		}
		else if (category == H_CATEGORY_FUNCTION)
		{
			try
			{
			FunctionNode *fNode = dynamic_cast<FunctionNode*> (node);
			double value = fNode->getValue ();
			std::cout << "  - Value: " << value << std::endl;
			}
			catch (const ExceptionHugin& e)
			{
			std::cout << "  - Value: N/A\n";
			}
		}
		else if (node->getKind() == H_KIND_DISCRETE)
		{
			DiscreteNode *dNode = dynamic_cast<DiscreteNode*> (node);

			for (size_t i = 0, n = dNode->getNumberOfStates(); i < n; i++)
			{
			std::cout << "  - " << dNode->getStateLabel (i)
				 << " " << dNode->getBelief (i);
			if (hasUtilities)
				std::cout << " (" << dNode->getExpectedUtility (i) << ")";
			std::cout << std::endl;
			}
		}
		else
		{
			ContinuousChanceNode *ccNode
			= dynamic_cast<ContinuousChanceNode*> (node);

			std::cout << "  - Mean : " << ccNode->getMean() << std::endl;
			std::cout << "  - SD   : " << sqrt (ccNode->getVariance()) << std::endl;
		}

	}


	



	//ADDIND NODE TEST
	









	/*remove( "C:/rewards.txt");
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

	//Broodwar->enableFlag(Flag::CompleteMapInformation);
	Broodwar->enableFlag(Flag::UserInput);
	
	//scoutingManager.AnalyzeMap();*/
}

void StarcraftAI::onEnd(bool isWinner)
{	

	/*StarcraftAI::reinforcementLearning.SaveCurrentWeightsToFile(); 

	gameCount++;
	BWAPI::Broodwar->restartGame();*/
}


void StarcraftAI::onFrame()
{
	
	TacticsManager::GetInstance()->Update();
	ScoutingManager::GetInstance()->Update();
	ProductionManager::GetInstance()->Update();
	WorkerManager::GetInstance()->Update();
	StrategyManager::GetInstance()->Update();

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
	else if(unit->getPlayer() == BWAPI::Broodwar->enemy())
	{
		ScoutingManager::GetInstance()->UnitFound(unit);
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


