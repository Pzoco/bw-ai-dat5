#include "ResearchTask.h"

ResearchTask::ResearchTask(BWAPI::TechType tech)
{
	techType = tech;
}

std::string ResearchTask::GetType()
{
	return "ResearchTask";
}