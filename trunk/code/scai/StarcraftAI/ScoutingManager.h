#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>

DWORD WINAPI AnalyzeThread();
class ScoutingManager
{
public:
	ScoutingManager();
	static bool IsMapAnalyzed();
	void AnalyzeMap();
	void Update();
};
