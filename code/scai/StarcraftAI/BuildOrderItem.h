#pragma once
#include <BWAPI.h>
#include "ScoutingManager.h"
#include "TacticsManager.h"
#include "Condition.h"


//The items in the build order - There is a constructor for adding one condition or a list
//Im only doing this type thing with an int because c++ is retarded
class BuildOrderItem
{
	public:
		enum Status{BuildStatus_NotStarted,BuildStatus_Started,BuildStatus_Processing,BuildStatus_Done};
		enum ProductionFocus{Focus_Workers,Focus_CombatUnits,Focus_Tech};
		std::list<Condition> GetConditions(){return conditions;}
		virtual int GetType(){return 0;}
	protected:
		std::list <Condition> conditions;
};
class ResearchItem: public BuildOrderItem
{
	public: 
		BWAPI::TechType techType;
		ResearchItem(BWAPI::TechType tech,Condition conditionToBeFulfilled): 
		techType(tech){conditions.push_back(conditionToBeFulfilled);}
		ResearchItem(BWAPI::TechType tech,std::list<Condition> conditionsToBeFulFilled): 
		techType(tech){for each(Condition c in conditionsToBeFulFilled){conditions.push_back(c);}}
		int GetType(){return 1;}
};	
class BuildingItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType building;
		Condition condition;
		BuildingItem(BWAPI::UnitType buildingToBeBuild,Condition conditionToBeFulfilled): 
		building(buildingToBeBuild){conditions.push_back(conditionToBeFulfilled);}
		BuildingItem(BWAPI::UnitType buildingToBeBuild,std::list<Condition> conditionsToBeFulFilled): 
		building(buildingToBeBuild){for each(Condition c in conditionsToBeFulFilled){conditions.push_back(c);}}
		int GetType(){return 2;}
};
class UnitProductionItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType unit;
		Condition condition;
		UnitProductionItem(BWAPI::UnitType unitToBeBuild, Condition conditionToBeFulfilled): 
		unit(unitToBeBuild){conditions.push_back(conditionToBeFulfilled);}			
		UnitProductionItem(BWAPI::UnitType unitToBeBuild,std::list<Condition> conditionsToBeFulFilled): 
		unit(unitToBeBuild){for each(Condition c in conditionsToBeFulFilled){conditions.push_back(c);}}
		int GetType(){return 3;}
};
class ProductionFocusItem: public BuildOrderItem
{
	public:
		BuildOrderItem::ProductionFocus productionFocus;
		std::list<Condition> conditions;
		ProductionFocusItem(BuildOrderItem::ProductionFocus productionFocusToBeFulfilled,Condition conditionToBeFulfilled): 
		productionFocus(productionFocusToBeFulfilled){conditions.push_back(conditionToBeFulfilled);}
		ProductionFocusItem(BuildOrderItem::ProductionFocus productionFocusToBeFulfilled,std::list<Condition> conditionsToBeFulFilled): 
		productionFocus(productionFocusToBeFulfilled){for each(Condition c in conditionsToBeFulFilled){conditions.push_back(c);}}
		int GetType(){return 4;}
};

