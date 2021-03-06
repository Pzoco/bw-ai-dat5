#pragma once
#include "Squad.h"
#include <BWAPI.h>
#include <BWTA.h>

class TacticsManager
{
public:
	static TacticsManager* GetInstance();
	void Update();
	void AddSquad(Squad squad);
	void RemoveSquad(Squad squad);
	void AssignToSquad(BWAPI::Unit* unit);
	void AssignToSquads(std::set<BWAPI::Unit*> units);
	void UnitKilled(BWAPI::Unit* unit);
	void MoveSquad(BWAPI::Position pos);
	int static GetNumberOfUnits(BWAPI::UnitType type);
	BWAPI::Position attackPos;
private:
	TacticsManager();
	static TacticsManager* tacticsManager;
	std::list<Squad> &GetRightSquadList(BWAPI::UnitType);
	void WriteSquadList(BWAPI::UnitType, std::list<Squad>);
};
