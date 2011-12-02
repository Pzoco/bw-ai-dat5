#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>

DWORD WINAPI AnalyzeThread();
class ScoutingManager
{
public:
	enum ThreatLevel {Low,Medium,High};
	ScoutingManager();
	static ThreatLevel threatLevel;
	static bool IsMapAnalyzed();
	void AnalyzeMap();
	void Update();
	ThreatLevel GetThreatLevel(){return threatLevel;}
	void IntialScout();
};
