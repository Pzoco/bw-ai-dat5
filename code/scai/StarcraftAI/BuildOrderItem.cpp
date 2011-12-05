#include "BuildOrderItem.h"

std::list <Condition*> BuildOrderItem::GetConditions()
{
	return conditions;
}
std::string BuildOrderItem::GetType()
{
	return type;
}
