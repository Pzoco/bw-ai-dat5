#include "BuildOrder.h"
#include <BWAPI.h>

std::list<BuildOrderItem*> items;

BuildOrder::BuildOrder()
{
}

void BuildOrder::AddItem(BuildOrderItem* buildOrderItem)
{
	items.push_back(buildOrderItem);
}

void BuildOrder::RemoveItem(BuildOrderItem* item)
{
	items.remove(item);
}

std::list<BuildOrderItem*> BuildOrder::GetBuildOrderItems()
{
	return items;
}
bool BuildOrder::IsEmpty()
{
	return items.empty();
}