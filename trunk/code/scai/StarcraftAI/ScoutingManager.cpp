#include "ScoutingManager.h"
#include <BWAPI.h>
#include <BWTA.h>

bool analyzed = false;

ScoutingManager::ScoutingManager()
{

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

void InitialScout(std::list<BWAPI::Unit*> scvs)
{
}	