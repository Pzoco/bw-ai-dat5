#pragma once
#include <BWAPI.h>
#include "ProductionTask.h"
#include "ScoutingManager.h"
#include "TacticsManager.h"
#include "Condition.h"


//The items in the build order - There is a constructor for adding one condition or a list
class BuildOrderItem
{
	public:
		std::list<Condition> GetConditions(){return conditions;}
		virtual std::string GetType()
	protected:
		std::list <Condition> conditions;
};
class ResearchItem: public BuildOrderItem
{
	public: 
		BWAPI::TechType techType;
		ResearchItem(BWAPI::TechType tech,Condition conditionToBeFulfilled)
		{
			techType = tech;
			conditions.push_back(conditionToBeFulfilled);
		}
		ResearchItem(BWAPI::TechType tech,std::list<Condition> conditionsToBeFulFilled)
		{
			techType = tech;
			for each(Condition c in conditionsToBeFulFilled)
			{
				conditions.push_back(c);
			}
		}
		std::string GetType(){return "ResearchItem";}
};	
class BuildingItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType building;
		ProductionEnums::BuildingPlacement buildingPlacement;
		BuildingItem(BWAPI::UnitType buildingToBeBuild,ProductionEnums::BuildingPlacement buildingPlacement,Condition conditionToBeFulfilled)
		{
			building = buildingToBeBuild;
			this->buildingPlacement = buildingPlacement;
			conditions.push_back(conditionToBeFulfilled);
		}
		BuildingItem(BWAPI::UnitType buildingToBeBuild,ProductionEnums::BuildingPlacement buildingPlacement,std::list<Condition> conditionsToBeFulFilled)
		{
			building = buildingToBeBuild;
			this->buildingPlacement = buildingPlacement;
			for each(Condition c in conditionsToBeFulFilled)
			{
				conditions.push_back(c);
			}
		}
		std::string GetType(){return "BuildingItem";}
};
class UnitProductionItem: public BuildOrderItem
{
	public: 
		BWAPI::UnitType unit;
		UnitProductionItem(BWAPI::UnitType unitToBeBuild, Condition conditionToBeFulfilled)
		{
			unit = unitToBeBuild;
			conditions.push_back(conditionToBeFulfilled);
		}			
		UnitProductionItem(BWAPI::UnitType unitToBeBuild,std::list<Condition> conditionsToBeFulFilled): unit(unitToBeBuild)
		{
			for each(Condition c in conditionsToBeFulFilled)
			{
				conditions.push_back(c);
			}
		}
		std::string GetType(){return "UnitProductionItem";}
};
class ProductionFocusItem
{
	std::list <Condition> conditions;
	public:
		ProductionEnums::ProductionFocus productionFocus;
		ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,Condition conditionToBeFulfilled)
		{
			productionFocus = productionFocusToBeFulfilled;
			conditions.push_back(conditionToBeFulfilled);
		}
		ProductionFocusItem(ProductionEnums::ProductionFocus productionFocusToBeFulfilled,std::list<Condition> conditionsToBeFulFilled)
		{
			productionFocus = productionFocusToBeFulfilled;
			for each(Condition c in conditionsToBeFulFilled)
			{
				conditions.push_back(c);
			}
		}
		std::string GetType(){return "ProductionFocusItem";}
};

