#pragma once
#include <BWAPI.h>
#include "Condition.h"

class BuildingProductionCondition: public Condition
{
	public: 
		BWAPI::UnitType buildingType; 
		int number;
		BuildingProductionCondition(BWAPI::UnitType buildingTypeToGet,int numberOfUnits):
		buildingType(buildingTypeToGet),number(numberOfUnits){}
		//bool IsFulfilled(){if(number==TacticsManager::GetNumberOfUnits(buildingType)){return true;}return false;}
};