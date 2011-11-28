#pragma once
#include <BWAPI.h>
#include "ScoutingManager.h"
#include "TacticsManager.h"
#include "BuildOrderItem.h"

//BuildOrder class
class BuildOrder
{
public:	
	BuildOrder();
	void AddItem(BuildOrderItem buildOrderItem);
	std::list<BuildOrderItem> GetBuildOrderItems();
};
