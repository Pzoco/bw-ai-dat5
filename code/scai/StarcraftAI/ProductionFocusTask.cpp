#include "ProductionFocusTask.h"

ProductionFocusTask::ProductionFocusTask(ProductionEnums::ProductionFocus focus)
{
	this->focus=focus;
}
std::string ProductionFocusTask::GetType()
{
	return "UnitProductionTask";
}