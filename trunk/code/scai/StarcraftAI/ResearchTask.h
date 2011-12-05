#pragma once
#include "ProductionTask.h"
#include <BWAPI.h>
class ResearchTask: public ProductionTask
{
public:
	BWAPI::TechType techType;
	std::string GetType();
	ResearchTask(BWAPI::TechType tech);

};