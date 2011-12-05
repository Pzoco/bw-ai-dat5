#include "ResearchTask.h"

ResearchTask::ResearchTask(BWAPI::TechType tech)
{
	techType = tech;
	mineralPrice = techType.mineralPrice();
	gasPrice = techType.gasPrice();
	requiredBuilding = techType.whatResearches();
}

std::string ResearchTask::GetType()
{
	return "ResearchTask";
}