#pragma once
#include "BaseTactic.h"
#include <BWAPI.h>
#include <BWTA.h>

class Vulture :
	public BaseTactic
{
public:
	Vulture(BWAPI::Unit* unit);
};
