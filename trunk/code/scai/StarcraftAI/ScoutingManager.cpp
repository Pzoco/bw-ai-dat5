#include "ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>
//#include "hugin"
bool analyzed = false;

ScoutingManager* ScoutingManager::scoutingManager = 0;

ScoutingManager::ScoutingManager(){}
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

}

void ScoutingManager::Scout(BWAPI::Unit* scv)
{
	//Scout the other bases
}	

int ScoutingManager::MostProbableEnemyPosition()
{
}