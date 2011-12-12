#include "ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>

bool analyzed = false;

ScoutingManager* ScoutingManager::scoutingManager = 0;
ScoutingManager::ScoutingManager()
{
	isScouting=false;
	enemyBaseFound=false;
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
void ScoutingManager::Update()
{
	//Broodwar->printf("Update");
	if(!isScouting)
	{
		Scout();
	}
	if(!enemyBaseFound)
	{
		std::set<BWAPI::Unit*> enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
		for(std::set<BWAPI::Unit*>::iterator i=enemyUnits.begin();i!=enemyUnits.end();i++)
		{
			Broodwar->printf("Searching...");
			if((*i)->getType() == BWAPI::UnitTypes::Terran_SCV 
				||(*i)->getType() == BWAPI::UnitTypes::Zerg_Drone
				||(*i)->getType() == BWAPI::UnitTypes::Protoss_Probe)
			{
				BWAPI::Broodwar->printf("Found Worker");
				InsertWorkerEvidence(*i);
			}
			if((*i)->getType() == BWAPI::UnitTypes::Terran_Command_Center
				|| (*i)->getType() == BWAPI::UnitTypes::Protoss_Nexus
				|| (*i)->getType() == BWAPI::UnitTypes::Zerg_Hatchery
				|| (*i)->getType() == BWAPI::UnitTypes::Zerg_Lair
				|| (*i)->getType() == BWAPI::UnitTypes::Zerg_Hive)
			{
				EnemyBaseFound((*i)->getTilePosition());
			}
		}
	}
	
}
void ScoutingManager::EnemyBaseFound(BWAPI::TilePosition basePosition)
{
	enemyBaseFound=true;
	WorkerManager::GetInstance()->ReturnSCV(scoutingSCV);
	Broodwar->printf("Found base");
}
void ScoutingManager::InsertWorkerEvidence(BWAPI::Unit *worker)
{
	//BWAPI::Broodwar->printf("insertWorkerEvidence");
	BWAPI::Position workerPosition=worker->getPosition();

	
	int time = BWAPI::Broodwar->elapsedTime();
	if(time<InformationEnums::AlmostNone)
	{
		BWAPI::Broodwar->printf("Almost None");
	}
	else if(time<InformationEnums::Fast)
	{
		BWAPI::Broodwar->printf("Fast");
	}
	else if(time<InformationEnums::Middle)
	{
		BWAPI::Broodwar->printf("Middle");
	}
	else if(time<InformationEnums::Long)
	{
		BWAPI::Broodwar->printf("Long");
	}
	else
	{
		BWAPI::Broodwar->printf("Really Long");
	}
	//workerPosition.x
	InformationEnums::Positions sector;
	sector=InformationEnums::NE;
	//BWAPI::Broodwar->printf("%d\n",sector);
	BWAPI::Broodwar->printf("%d,%d     %d",workerPosition.x()/32,workerPosition.y()/32,BWAPI::Broodwar->mapWidth());
	if(workerPosition.x()/32<=BWAPI::Broodwar->mapWidth()/2)//West
	{
		if(workerPosition.y()/32<=BWAPI::Broodwar->mapHeight()/2)//North
		{
			sector= InformationEnums::NW;
			BWAPI::Broodwar->printf("NW");
		}
		if(workerPosition.y()/32>BWAPI::Broodwar->mapHeight()/2)//South
		{
			sector = InformationEnums::SW;
			BWAPI::Broodwar->printf("SW");
		}
	}
	else if(workerPosition.x()/32>BWAPI::Broodwar->mapWidth()/2)//East
	{
		if(workerPosition.y()/32<=BWAPI::Broodwar->mapHeight()/2)//North
		{
			sector = InformationEnums::NE;
			BWAPI::Broodwar->printf("NE");
		}
		if(workerPosition.y()/32>BWAPI::Broodwar->mapHeight()/2)//South
		{
			sector = InformationEnums::SE;
			BWAPI::Broodwar->printf("SE");
		}
	}
	else
		BWAPI::Broodwar->printf("NON");


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
	scoutingSCV=WorkerManager::GetInstance()->RequestSCV();

	//move to the most probable location

	//BWAPI::Position tempPosition(BWAPI::TilePosition(Broodwar->mapWidth(),Broodwar->mapHeight()));
	std::set<BWAPI::TilePosition> startPositions = BWAPI::Broodwar->getStartLocations();
	for(std::set<BWAPI::TilePosition>::iterator i=startPositions.begin();i!=startPositions.end();i++)
	{
		if((*i)!= Broodwar->self()->getStartLocation())
		{
			scoutingSCV->move(Position(*i),true);
		}
	}
	isScouting=true;
	//Scout the other bases
	//get most probable enemy position and send the scout to it
	//currently going to all bases in order
	//if there are equal probability ones we can send it to the closer one
}	

int ScoutingManager::MostProbableEnemyPosition()
{
	//get the most probable enemyposition
}

