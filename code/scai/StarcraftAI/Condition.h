#pragma once
#include <BWAPI.h>
#include "ScoutingManager.h"
#include "TacticsManager.h"


//Conditions for starting building/Producing etc - 
struct Condition
{
	public: 
		virtual bool IsFulfilled(){return true;}
};
class SupplyCondition: public Condition
{
	public:	
		int supply;
		SupplyCondition(int supplyToReach):supply(supplyToReach){}
		bool IsFulfilled(){if(supply>=BWAPI::Broodwar->self()->supplyUsed()){return true;}return false;}
};
class ThreatLevelCondition: public Condition
{
	public:
		ScoutingManager::ThreatLevel threatLevel;
		ThreatLevelCondition(ScoutingManager::ThreatLevel threatLevelToReach):threatLevel(threatLevelToReach){}
		bool IsFulfilled(){if(threatLevel == ScoutingManager::threatLevel){return true;}return false;}
		
};
class UnitProductionCondition: public Condition
{
	public: 
		BWAPI::UnitType unitType; 
		int number;
		UnitProductionCondition(BWAPI::UnitType unitTypeToGet,int numberOfUnits):
		unitType(unitTypeToGet),number(numberOfUnits){}
		//bool IsFulfilled(){if(number==TacticsManager::GetNumberOfUnits(unitType)){return true;}return false;}
};

class BuildingProductionCondition: public Condition
{
	public: 
		BWAPI::UnitType buildingType; 
		int number;
		BuildingProductionCondition(BWAPI::UnitType buildingTypeToGet,int numberOfUnits):
		buildingType(buildingTypeToGet),number(numberOfUnits){}
		//bool IsFulfilled(){if(number==TacticsManager::GetNumberOfUnits(buildingType)){return true;}return false;}
};
