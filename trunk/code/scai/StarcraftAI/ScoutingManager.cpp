#include "ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>

bool analyzed = false;

ScoutingManager* ScoutingManager::scoutingManager = 0;
ScoutingManager::ScoutingManager()
{
	isScouting=false;
	enemyBaseFound=false;
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

	spawnPredictor.PrintNodes();
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
	if(!enemyBaseFound)
	{
		std::set<BWAPI::Unit*> enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
		for(std::set<BWAPI::Unit*>::iterator i=enemyUnits.begin();i!=enemyUnits.end();i++)
		{
			Broodwar->printf("Searching...");
						if((*i)->getType() == BWAPI::UnitTypes::Terran_Command_Center
				|| (*i)->getType() == BWAPI::UnitTypes::Protoss_Nexus
				|| (*i)->getType() == BWAPI::UnitTypes::Zerg_Hatchery
				|| (*i)->getType() == BWAPI::UnitTypes::Zerg_Lair
				|| (*i)->getType() == BWAPI::UnitTypes::Zerg_Hive)
			{

				
				spawnPredictor.EnterEvidence("EnemySpawn",EnumToString(PositionToEnum((*i)->getPosition())));				
				EnemyBaseFound((*i)->getTilePosition());
			}
			if((*i)->getType() == BWAPI::UnitTypes::Terran_SCV 
				||(*i)->getType() == BWAPI::UnitTypes::Zerg_Drone
				||(*i)->getType() == BWAPI::UnitTypes::Protoss_Probe)
			{
				BWAPI::Broodwar->printf("Found Worker");
				//InsertWorkerEvidence(*i);
			}

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
	WorkerManager::GetInstance()->ReturnSCV(scoutingSCV);

}
void ScoutingManager::InsertWorkerEvidence(BWAPI::Unit *worker)
{
	//BWAPI::Broodwar->printf("insertWorkerEvidence");
	BWAPI::Position workerPosition=worker->getPosition();

	/*
	int time = BWAPI::Broodwar->elapsedTime();
	if(time<InformationEnums::AlmostNone)
	{
		spawnPredictor.EnterEvidence("TimingSeenTo","AlmostNone");
		BWAPI::Broodwar->printf("Almost None");
	}
	else if(time<InformationEnums::Fast)
	{
		spawnPredictor.EnterEvidence("TimingSeenTo","Early");
		BWAPI::Broodwar->printf("Early");
	}
	else if(time<InformationEnums::Middle)
	{
		spawnPredictor.EnterEvidence("TimingSeenTo","Middle");
		BWAPI::Broodwar->printf("Middle");
	}
	else if(time<InformationEnums::Long)
	{
		spawnPredictor.EnterEvidence("TimingSeenTo","Late");
		BWAPI::Broodwar->printf("Late");
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
			spawnPredictor.EnterEvidence("WorkerScoutPositionTo","NW");	
		}
		if(workerPosition.y()/32>BWAPI::Broodwar->mapHeight()/2)//South
		{
			sector = InformationEnums::SW;
			BWAPI::Broodwar->printf("SW");
			spawnPredictor.EnterEvidence("WorkerScoutPositionTo","NW");	
		}
	}
	else if(workerPosition.x()/32>BWAPI::Broodwar->mapWidth()/2)//East
	{
		if(workerPosition.y()/32<=BWAPI::Broodwar->mapHeight()/2)//North
		{
			sector = InformationEnums::NE;
			BWAPI::Broodwar->printf("NE");
			spawnPredictor.EnterEvidence("WorkerScoutPositionTo","NW");	
		}
		if(workerPosition.y()/32>BWAPI::Broodwar->mapHeight()/2)//South
		{
			sector = InformationEnums::SE;
			BWAPI::Broodwar->printf("SE");
			spawnPredictor.EnterEvidence("WorkerScoutPositionTo","NW");	
		}
	}
	else
		BWAPI::Broodwar->printf("NON");

*/
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
	scoutingSCV->move(EnumToPosition(MostProbableEnemyPosition()));
	//std::set<BWAPI::TilePosition> startPositions = BWAPI::Broodwar->getStartLocations();
	//for(std::set<BWAPI::TilePosition>::iterator i=startPositions.begin();i!=startPositions.end();i++)
	{
		
	}
	isScouting=true;
	//Scout the other bases
	//get most probable enemy position and send the scout to it
	//currently going to all bases in order
	//if there are equal probability ones we can send it to the closer one
}	

InformationEnums::Positions ScoutingManager::MostProbableEnemyPosition()
{
	//get the most probable enemyposition
	InformationEnums::Positions position;
	float highest;
	highest=spawnPredictor.GetProbability("EnemyBase","NE");
	position=InformationEnums::NE;
	if(highest<spawnPredictor.GetProbability("EnemyBase","SE"))
	{
		highest=spawnPredictor.GetProbability("EnemyBase","SE");
		position=InformationEnums::SE;
	}
	if(highest<spawnPredictor.GetProbability("EnemyBase","SW"))
	{
		highest=spawnPredictor.GetProbability("EnemyBase","SW");
		position=InformationEnums::SW;
	}
	if(highest<spawnPredictor.GetProbability("EnemyBase","NW"))
	{
		highest=spawnPredictor.GetProbability("EnemyBase","NW");
		position=InformationEnums::NW;
	}

	return position;
}

InformationEnums::Positions ScoutingManager::PositionToEnum(BWAPI::Position position)
{
	if(position.x()>= Broodwar->mapWidth()/2 && position.y()< Broodwar->mapHeight()/2)
	{
		return InformationEnums::NE;
	}
	else if(position.x()>= Broodwar->mapWidth()/2 && position.y()>= Broodwar->mapHeight()/2) 
	{
		return InformationEnums::SE;
	}
	else if(position.x()< Broodwar->mapWidth()/2 && position.y()>= Broodwar->mapHeight()/2)
	{
		return InformationEnums::SW;
	}
	else if(position.x()< Broodwar->mapWidth()/2 && position.y()< Broodwar->mapHeight()/2)
	{
		return InformationEnums::NW;
	}
	else
	{
		Broodwar->printf("Position to enums error");
		return InformationEnums::NE;
	}
}

BWAPI::Position ScoutingManager::EnumToPosition(InformationEnums::Positions enumPosition)
{
	Position tempPosition;
	std::set<BWAPI::TilePosition> startPositions = BWAPI::Broodwar->getStartLocations();
	for(std::set<BWAPI::TilePosition>::iterator i=startPositions.begin();i!=startPositions.end();i++)
	{
		
		if(enumPosition==InformationEnums::NE && (*i).x()>=Broodwar->mapWidth()/2 && (*i).y()<Broodwar->mapWidth()/2)
		{
			tempPosition = Position((*i));
			return tempPosition;
		}
		else if(enumPosition==InformationEnums::SE && (*i).x()>=Broodwar->mapWidth()/2 && (*i).y()>=Broodwar->mapWidth()/2)
		{
			tempPosition = Position((*i));
			return tempPosition;
		}
		else if(enumPosition==InformationEnums::SW && (*i).x()<Broodwar->mapWidth()/2 && (*i).y()>=Broodwar->mapWidth()/2)
		{
			tempPosition = Position((*i));
			return tempPosition;
		}
		else if(enumPosition==InformationEnums::SE && (*i).x()<Broodwar->mapWidth()/2 && (*i).y()<Broodwar->mapWidth()/2)
		{
			tempPosition = Position((*i));
			return tempPosition;
		}

	}

			Broodwar->printf("EnumToPositionConversion Error");
			tempPosition = Position(0,0);
			return tempPosition;
}

std::string ScoutingManager::EnumToString(InformationEnums::Positions position)
{
	if(position==InformationEnums::NE)
		return "NE";
	else if(position==InformationEnums::SE)
		return "SE";
	else if(position==InformationEnums::SW)
		return "SW";
	else
		return "NW";
}