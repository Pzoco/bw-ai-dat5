#include "BuildOrder.h"
#include <BWAPI.h>

std::list<BuildOrderItem> items;
BuildOrder::BuildOrder()
{
	
}

void BuildOrder::AddItem(BuildOrderItem buildOrderItem)
{
	items.push_back(buildOrderItem);
}

std::list<BuildOrderItem> BuildOrder::GetBuildOrderItems()
{
	return items;
}