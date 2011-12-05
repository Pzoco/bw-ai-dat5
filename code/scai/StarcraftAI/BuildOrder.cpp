#include "BuildOrder.h"
#include <BWAPI.h>


BuildOrder::BuildOrder(std::string name)
{
	this->name = name;
}

void BuildOrder::AddItem(BuildOrderItem* buildOrderItem)
{
	items.push_back(buildOrderItem);
}

void BuildOrder::RemoveItem(BuildOrderItem* item)
{
	for(std::list<BuildOrderItem*>::iterator pItem = items.begin();pItem!=items.end();pItem++)
	{
		if( *pItem == item)
		{
			items.erase(pItem);
			break;
		}
	}
}

std::list<BuildOrderItem*> BuildOrder::GetBuildOrderItems()
{
	return items;
}
bool BuildOrder::IsEmpty()
{
	return items.empty();
}

int BuildOrder::GetSize()
{
	return items.size();
}