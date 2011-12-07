#pragma once
#include <BWAPI.h>
#include "BuildOrderItem.h"

//BuildOrder class
class BuildOrder
{
public:	
	BuildOrder(std::string name);
	std::string name;
	std::list<BuildOrderItem*> items;
	void AddItem(BuildOrderItem* buildOrderItem);
	void RemoveItem(BuildOrderItem* item);
	std::list<BuildOrderItem*> GetBuildOrderItems();
	bool IsEmpty();
	int GetSize();
};
