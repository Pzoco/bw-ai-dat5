#include "ThreatLevelCondition.h"
#include "ScoutingManager.h"
#include <BWAPI.h>

ThreatLevelCondition::ThreatLevelCondition(InformationEnums::ThreatLevel threatLevelToReach)
{
	level = threatLevelToReach;
}
bool ThreatLevelCondition::IsFulfilled()
{
	//Gives linker error if that static member is used
	/*if(level == ScoutingManager::currentThreatLevel)
	{
		return true;
	}*/
	return false;
}

