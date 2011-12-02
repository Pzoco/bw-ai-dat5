#include "BuildingPlacer.h"
#include <BWAPI.h>
#include "WorkerManager.h"

BuildingPlacer::BuildingPlacer(void)
{
	
}

void BuildingPlacer::AddScv(BWAPI::Unit* unit)
{
	
}
void BuildingPlacer::Construct(BWAPI::UnitType buildingType, BuildingPlacer::Placement)
{
	BWAPI::Unit* unit = WorkerManager::GetScv()
}