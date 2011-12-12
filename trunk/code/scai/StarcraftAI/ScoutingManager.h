#pragma once
#include "WorkerManager.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include "InformationEnums.h"
#include "WorkerManager.h"

using namespace BWAPI;
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
	void Scout();
	int MostProbableEnemyPosition();
	void InsertWorkerEvidence(BWAPI::Unit *worker);
	void VisitBase(InformationEnums::Positions position,BWAPI::Unit* scv);
	void EnemyBaseFound(BWAPI::TilePosition enemyBase);
private:
	Unit* scoutingSCV;
	bool enemyBaseFound;
	bool isScouting;
	ScoutingManager();
	std::list<BWAPI::Unit*> enemyUnits;
	std::list<BWAPI::Unit*> enemyBuildings;
	static ScoutingManager* scoutingManager;
};