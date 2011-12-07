#include "UpgradeTask.h"

UpgradeTask::UpgradeTask(BWAPI::UpgradeType tech)
{
	techType = tech;
}

std::string UpgradeTask::GetType()
{
	return "UpgradeTask";
}