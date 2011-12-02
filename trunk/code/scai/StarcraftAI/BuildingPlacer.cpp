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

	BWAPI::Unit* builder = WorkerManager::GetScv()
	builder->build(Get the tile position,buildingType);

	int width = buildingType.tileWidth();
	int height = buildingType.tileHeight();
	
	//takes into account addons
	if (buildingType==BWAPI::UnitTypes::Terran_Command_Center ||
		buildingType==BWAPI::UnitTypes::Terran_Factory || 
		buildingType==BWAPI::UnitTypes::Terran_Starport ||
		buildingType==BWAPI::UnitTypes::Terran_Science_Facility)
	{
		width+=2;
	}
	
	if(buildingType==BWAPI::UnitTypes::Terran_Refinery)
	{
		//build a refinery by your base
	}


	

  
}