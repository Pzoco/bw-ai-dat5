#pragma once
#include "UnitAgent.h"
#include <BWAPI.h>
#include <BWTA.h>

class Vulture :
	public UnitAgent
{
public:
	Vulture(BWAPI::Unit* unit);
};
