#pragma once
#include "ProductionTask.h"
#include <BWAPI.h>
class UpgradeTask: public ProductionTask
{
public:
	BWAPI::UpgradeType techType;
	std::string GetType();
	UpgradeTask(BWAPI::UpgradeType tech);

};