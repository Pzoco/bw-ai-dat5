#include "ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>

bool analyzed = false;

ScoutingManager* ScoutingManager::scoutingManager = 0;
ScoutingManager::ScoutingManager()
{
	isScouting=false;
	enemyBaseFound=false;
	enemyScoutFound=false;
	spawnPredictor=BayesianNetwork("C:\\SpawnPrediction.net");
	
	TilePosition position(Broodwar->self()->getStartLocation());
	if(position.x()>=Broodwar->mapWidth()/2 && position.y()<Broodwar->mapWidth()/2)
	{
		spawnPredictor.EnterEvidence("OurSpawn","NE");
	}
	if(position.x()>=Broodwar->mapWidth()/2 && position.y()>=Broodwar->mapWidth()/2)
	{
		spawnPredictor.EnterEvidence("OurSpawn","SE");
	}
	if(position.x()<Broodwar->mapWidth()/2 && position.y()>=Broodwar->mapWidth()/2)
	{
		spawnPredictor.EnterEvidence("OurSpawn","SW");
	}
	if(position.x()<Broodwar->mapWidth()/2 && position.y()<Broodwar->mapWidth()/2)
	{
		spawnPredictor.EnterEvidence("OurSpawn","NW");
	}
	scoutingSCV = NULL;
}
ScoutingManager* ScoutingManager::GetInstance()
{
	if(scoutingManager==NULL)
	{
		scoutingManager = new ScoutingManager();
	}
	return scoutingManager;
}


DWORD WINAPI AnalyzeThread()
{
	BWTA::analyze();
	analyzed = true;
	BWAPI::Broodwar->printf("Analyzed map");
	return 0;
}
bool ScoutingManager::IsMapAnalyzed()
{
	return analyzed;
}

void ScoutingManager::AnalyzeMap()
{
	BWTA::readMap();
	//Creates a thread for analyzing the map, because this can take a very long time. 
	//Code borrowed from ExampleAIModule
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
}

void ScoutingManager::UnitFound(BWAPI::Unit* unit)
{
	if(!enemyBaseFound)
	{
		if((unit)->getType() == BWAPI::UnitTypes::Terran_Command_Center
			|| (unit)->getType() == BWAPI::UnitTypes::Protoss_Nexus
			|| (unit)->getType() == BWAPI::UnitTypes::Zerg_Hatchery
			|| (unit)->getType() == BWAPI::UnitTypes::Zerg_Lair
			|| (unit)->getType() == BWAPI::UnitTypes::Zerg_Hive)
		{
			EnemyBaseFound((unit)->getTilePosition());
		}
		if((unit)->getType() == BWAPI::UnitTypes::Terran_SCV 
			||(unit)->getType() == BWAPI::UnitTypes::Zerg_Drone
			||(unit)->getType() == BWAPI::UnitTypes::Protoss_Probe)
		{
			if(!enemyScoutFound)
			{
				enemyScoutFound = true;
				InsertWorkerEvidence(unit);
			}
		}
	}
	if(unit->getType().isBuilding())
	{


		bool found=false;
		for each (BWAPI::Unit* building in enemyBuildings[unit->getType()])
		{
			if(building->getID()==unit->getID())
			{
				found=true;
				break;
			}
		}
		if(!found)
		{
			Broodwar->printf("The unit is %s",unit->getType().getName().c_str());
			StrategyManager::GetInstance()->NewEnemyFound(unit);
			enemyBuildings[unit->getType()].push_back(unit);
		}

	}
	else
	{
		enemyUnits[unit->getType()].push_back(unit);
	}
}


void ScoutingManager::Update()
{
	if(Broodwar->getFrameCount()%50 == 0)
	{
		spawnPredictor.PrintToFile("EnemySpawn");
		//BWAPI::Broodwar->printf("Predicting now! 'frame %d",Broodwar->getFrameCount());
	}
	if(scoutingSCV != NULL)
	{
		if(isScouting && scoutingSCV->getDistance(scoutingGoal)<5 && !enemyBaseFound && scoutingSCV->exists())
		{
			isScouting = false;
			if(currentBest == InformationEnums::NE)//NE
				spawnPredictor.EnterEvidence("EnemyNotAtNE","True");
			else if(currentBest == InformationEnums::SE) //SE
				spawnPredictor.EnterEvidence("EnemyNotAtSE","True");
			else if(currentBest == InformationEnums::SW)//SW
				spawnPredictor.EnterEvidence("EnemyNotAtSW","True");
			else if(currentBest == InformationEnums::NW)//NW
				spawnPredictor.EnterEvidence("EnemyNotAtNW","True");
			Scout();
		}
	}
}
void ScoutingManager::EnemyBaseFound(BWAPI::TilePosition basePosition)
{
	TilePosition mapSize(Broodwar->mapWidth()*32,Broodwar->mapHeight()*32);
	if(basePosition.x()>=mapSize.x()/2 && basePosition.x()<mapSize.y()/2)//NE
	{
		spawnPredictor.EnterEvidence("EnemySpawn","NE");
	}
	else if(basePosition.x()>=mapSize.x()/2 && basePosition.y()>=mapSize.y()/2) //SE
	{
		spawnPredictor.EnterEvidence("EnemySpawn","SE");
	}
	else if(basePosition.x()<mapSize.x()/2 && basePosition.y()>=mapSize.y()/2)//SW
	{
		spawnPredictor.EnterEvidence("EnemySpawn","SW");
	}
	else if(basePosition.x()<mapSize.x()/2 && basePosition.x()<mapSize.y()/2)//NW
	{
		spawnPredictor.EnterEvidence("EnemySpawn","NW");
	}
	enemyBaseFound=true;
	enemyBasePosition = BWAPI::Position(basePosition);
	WorkerManager::GetInstance()->ReturnSCV(scoutingSCV);
	scoutingSCV = NULL;

}
void ScoutingManager::InsertWorkerEvidence(BWAPI::Unit *worker)
{
	//BWAPI::Broodwar->printf("insertWorkerEvidence");
	BWAPI::Position workerPosition=worker->getPosition();


	int time = BWAPI::Broodwar->elapsedTime();
	if(time<InformationEnums::AlmostNone)
	{
		spawnPredictor.EnterEvidence("TimingSeen","AlmostNone");
		//BWAPI::Broodwar->printf("Almost None");
	}
	else if(time<InformationEnums::Fast)
	{
		spawnPredictor.EnterEvidence("TimingSeen","Early");
		//BWAPI::Broodwar->printf("Early");
	}
	else if(time<InformationEnums::Middle)
	{
		spawnPredictor.EnterEvidence("TimingSeen","Middle");
		//BWAPI::Broodwar->printf("Middle");
	}
	else if(time<InformationEnums::Long)
	{
		spawnPredictor.EnterEvidence("TimingSeen","Late");
		//BWAPI::Broodwar->printf("Late");
	}
	else
	{
		//BWAPI::Broodwar->printf("Really Long");
	}

	InformationEnums::Positions sector;
	sector=InformationEnums::NE;
	//BWAPI::Broodwar->printf("%d\n",sector);
	//BWAPI::Broodwar->printf("%d,%d     %d",workerPosition.x()/32,workerPosition.y()/32,BWAPI::Broodwar->mapWidth());
	if(workerPosition.x()/32<=BWAPI::Broodwar->mapWidth()/2)//West
	{
		if(workerPosition.y()/32<=BWAPI::Broodwar->mapHeight()/2)//North
		{
			sector= InformationEnums::NW;
			//BWAPI::Broodwar->printf("NW");
			spawnPredictor.EnterEvidence("WorkerScoutPosition","NW");	
		}
		if(workerPosition.y()/32>BWAPI::Broodwar->mapHeight()/2)//South
		{
			sector = InformationEnums::SW;
			//BWAPI::Broodwar->printf("SW");
			spawnPredictor.EnterEvidence("WorkerScoutPosition","SW");	
		}
	}
	else if(workerPosition.x()/32>BWAPI::Broodwar->mapWidth()/2)//East
	{
		if(workerPosition.y()/32<=BWAPI::Broodwar->mapHeight()/2)//North
		{
			sector = InformationEnums::NE;
			//BWAPI::Broodwar->printf("NE");
			spawnPredictor.EnterEvidence("WorkerScoutPosition","NE");	
		}
		if(workerPosition.y()/32>BWAPI::Broodwar->mapHeight()/2)//South
		{
			sector = InformationEnums::SE;
			//BWAPI::Broodwar->printf("SE");
			spawnPredictor.EnterEvidence("WorkerScoutPosition","SE");	
		}
	}
}
void ScoutingManager::VisitBase(InformationEnums::Positions position,BWAPI::Unit* scv)
{
	std::set<BWAPI::TilePosition> spawnLocations=BWAPI::Broodwar->getStartLocations();
	if(position=InformationEnums::NE)
	{
		for(std::set<BWAPI::TilePosition>::iterator i=spawnLocations.begin();i!=spawnLocations.end();i++)
		{
			if((*i).x()/32>BWAPI::Broodwar->mapWidth()/2 && (*i).y()/32<=BWAPI::Broodwar->mapHeight()/2)
				scv->move(BWAPI::Position((*i)));
		}
	}
	else if(position=InformationEnums::SE)
	{
		for(std::set<BWAPI::TilePosition>::iterator i=spawnLocations.begin();i!=spawnLocations.end();i++)
		{
			if((*i).x()/32>BWAPI::Broodwar->mapWidth()/2 && (*i).y()/32>BWAPI::Broodwar->mapHeight()/2)
				scv->move(BWAPI::Position((*i)));
		}
	}
	else if(position=InformationEnums::SW)
	{
		for(std::set<BWAPI::TilePosition>::iterator i=spawnLocations.begin();i!=spawnLocations.end();i++)
		{
			if((*i).x()/32<=BWAPI::Broodwar->mapWidth()/2 && (*i).y()/32>BWAPI::Broodwar->mapHeight()/2)
				scv->move(BWAPI::Position((*i)));
		}
	}
	else if(position=InformationEnums::NW)
	{
		for(std::set<BWAPI::TilePosition>::iterator i=spawnLocations.begin();i!=spawnLocations.end();i++)
		{
			if((*i).x()/32<=BWAPI::Broodwar->mapWidth()/2 && (*i).y()/32<=BWAPI::Broodwar->mapHeight()/2)
				scv->move(BWAPI::Position((*i)));
		}
	}

}
void ScoutingManager::Scout()
{

	Broodwar->printf("Scout");
	if(scoutingSCV==NULL)
		scoutingSCV=WorkerManager::GetInstance()->RequestSCV();

	//move to the most probable location
	currentBest=MostProbableEnemyPosition();
	std::set<BWAPI::TilePosition> startPositions = BWAPI::Broodwar->getStartLocations();

	for(std::set<BWAPI::TilePosition>::iterator i=startPositions.begin();i!=startPositions.end();i++)
	{
		//Broodwar->printf("Width:%d  Height:%d   Map%d  %d",(*i).x(),(*i).y(), Broodwar->mapWidth(),Broodwar->mapHeight());
		if((currentBest==InformationEnums::NE && (*i).x() >= Broodwar->mapWidth()/2 && (*i).y()<Broodwar->mapHeight()/2)
			||(currentBest==InformationEnums::SE && (*i).x() >= Broodwar->mapWidth()/2 && (*i).y()>=Broodwar->mapHeight()/2)
			||(currentBest==InformationEnums::SW && (*i).x() < Broodwar->mapWidth()/2 && (*i).y()>=Broodwar->mapHeight()/2)
			||(currentBest==InformationEnums::NW && (*i).x() < Broodwar->mapWidth()/2 && (*i).y()<Broodwar->mapHeight()/2))
		{
			scoutingGoal = Position(*i);
			scoutingSCV->move(Position((*i)));
		}
	}

	isScouting=true;
	//Scout the other bases
	//get mostg probable enemy position and send the scout to it
	//currently going to all bases in order
	//if there are equal probability ones we can send it to the closer one
}	

InformationEnums::Positions ScoutingManager::MostProbableEnemyPosition()
{
	//get the most probable enemyposition
	InformationEnums::Positions position;
	float highest;
	highest=spawnPredictor.GetProbability("EnemySpawn","NE");
	
	position=InformationEnums::NE;
	if(highest<spawnPredictor.GetProbability("EnemySpawn","SE"))
	{
		highest=spawnPredictor.GetProbability("EnemySpawn","SE");
		position=InformationEnums::SE;
		//Broodwar->printf("SE");
	}
	if(highest<spawnPredictor.GetProbability("EnemySpawn","SW"))
	{
		//Broodwar->printf("SW");
		highest=spawnPredictor.GetProbability("EnemySpawn","SW");
		position=InformationEnums::SW;

	}
	if(highest<spawnPredictor.GetProbability("EnemySpawn","NW"))
	{
		//Broodwar->printf("NW");
		highest=spawnPredictor.GetProbability("EnemySpawn","NW");
		position=InformationEnums::NW;
	}

	return position;
}

BWAPI::Position ScoutingManager::GetEnemyPosition()
{
	return enemyBasePosition;
}