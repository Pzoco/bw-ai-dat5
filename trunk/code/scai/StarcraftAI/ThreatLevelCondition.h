#pragma once
#include <BWAPI.h>
#include "Condition.h"
#include "ScoutingManager.h"

class ThreatLevelCondition: public Condition
{
	public:
		ScoutingManager::ThreatLevel threatLevel;
		ThreatLevelCondition(ScoutingManager::ThreatLevel threatLevelToReach):threatLevel(threatLevelToReach){}
		bool IsFulfilled(){if(threatLevel == ScoutingManager::threatLevel){return true;}return false;}
		
};