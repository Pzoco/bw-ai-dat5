#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include "InformationEnums.h"
#include "WorkerManager.h"

DWORD WINAPI AnalyzeThread();

class ScoutingManager
{
public:
	static ScoutingManager* GetInstance();
	static bool IsMapAnalyzed();
	void AddEnemyUnit(BWAPI::Unit* unit);
	void AddEnemyBuilding(BWAPI::Unit* building);
	void AnalyzeMap();
	void Update();
	void Scout(BWAPI::Unit* scv);
	int MostProbableEnemyPosition();
	void InsertWorkerEvidence(BWAPI::Unit *worker);
	void VisitBase(InformationEnums::Positions position,BWAPI::Unit* scv);
private:
	ScoutingManager();
	std::list<BWAPI::Unit*> enemyUnits;
	std::list<BWAPI::Unit*> enemyBuildings;
	static ScoutingManager* scoutingManager;
};