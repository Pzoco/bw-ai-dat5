#pragma once
#include "WorkerManager.h"
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include "InformationEnums.h"
#include "WorkerManager.h"
#include "BayesianNetwork.h"
//#include <string>

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
	InformationEnums::Positions MostProbableEnemyPosition();
	void InsertWorkerEvidence(BWAPI::Unit *worker);
	void VisitBase(InformationEnums::Positions position,BWAPI::Unit* scv);
	void EnemyBaseFound(BWAPI::TilePosition enemyBase);
	void UnitFound(Unit* unit);
private:
	Unit* scoutingSCV;
	BayesianNetwork spawnPredictor;
	bool enemyBaseFound;
	bool isScouting;
	ScoutingManager();
	std::list<BWAPI::Unit*> enemyUnits;
	std::list<BWAPI::Unit*> enemyBuildings;
	static ScoutingManager* scoutingManager;
};