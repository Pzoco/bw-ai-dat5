#pragma once
#include "InformationEnums.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <BWAPI.h>
#include "hugin"

using namespace HAPI;
class StrategyManager
{
public:
	static StrategyManager* GetInstance();
	void Update();
private:
	bool initialized;
	std::string networksFilePath;
	InformationEnums::ThreatLevel currentThreatLevel;
	InformationEnums::Matchup matchup;
	Domain predictionNetwork;
	static StrategyManager* strategyManager;
	StrategyManager(void);
	std::string StrategyManager::TCHARToString(const TCHAR* ptsz)
	{
		int len = wcslen((wchar_t*)ptsz);
		char* psz = new char[2*len + 1];
		wcstombs(psz, (wchar_t*)ptsz, 2*len + 1);
		std::string s = psz;
		delete [] psz;
		return s;
	}
	std::string StrategyManager::ExePath() 
	{
		TCHAR buffer[MAX_PATH];
		GetModuleFileName( NULL, buffer, MAX_PATH );
		std::string convertedString = TCHARToString(buffer);
		std::string::size_type pos = std::string( convertedString ).find_last_of( "\\/" );
		std::string fullPath = std::string( convertedString ).substr( 0, pos);
		std::string::size_type pos2 = std::string( fullPath.c_str() ).find_last_of( "\\" );
		return std::string( convertedString ).substr( 0, pos2)+"\\";
	}
	void InitializePredictionNetwork();
};
