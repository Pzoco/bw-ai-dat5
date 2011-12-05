#pragma once
#include <BWAPI.h>
#include "Condition.h"
#include "ScoutingManager.h"

class ThreatLevelCondition: public Condition
{
	public:
		InformationEnums::ThreatLevel level;
		ThreatLevelCondition(InformationEnums::ThreatLevel threatLevelToReach);
		bool IsFulfilled();
};