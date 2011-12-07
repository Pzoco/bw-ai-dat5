#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include "InformationEnums.h"


DWORD WINAPI AnalyzeThread();

class ScoutingManager
{
public:
	static ScoutingManager* GetInstance();
	InformationEnums::ThreatLevel currentThreatLevel;
	static bool IsMapAnalyzed();
	void AnalyzeMap();
	void Update();
	void Scout(BWAPI::Unit* scv);
private:
	ScoutingManager();
	static ScoutingManager* scoutingManager;
};