#pragma once
#include "ProductionEnums.h"

class ProductionTask
{
public:
	int mineralPrice;
	int gasPrice;
	virtual std::string GetType(){return "Empty";}
protected:
	BWAPI::UnitType requiredBuilding;
};

class ConstructionTask: public ProductionTask
{
public:
	BWAPI::UnitType building;
	ProductionEnums::BuildingPlacement placement;
	ConstructionTask(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement)
	{
		building = buildingType;
		buildingPlacement = placement;
		mineralPrice = building.mineralPrice();
		gasPrice = building.gasPrice();
	}
	std::string GetType(){return "ConstructionTask";}
};

class ResearchTask: public ProductionTask
{
public:
	BWAPI::TechType techType;
	std::string GetType(){return "ResearchTask";}
	ResearchTask(BWAPI::TechType tech)
	{
		techType = tech;
		mineralPrice = techType.mineralPrice();
		gasPrice = techType.gasPrice();
		requiredBuilding = techType.whatResearches();
	}
};

class UnitProductionTask: public ProductionTask
{
public:
	BWAPI::UnitType unit;
	std::map<BWAPI::UnitType,int> requiredBuildings;
	UnitProductionTask(BWAPI::UnitType unitType)
	{
		unit = unitType;
		mineralPrice = unit.mineralPrice();
		gasPrice = unit.gasPrice();
		requiredBuildings = unit.requiredUnits();
	}
	std::string GetType(){return "UnitProductionTask";}
};
class ProductionFocusTask: public ProductionTask
{
public:
	ProductionEnums::ProductionFocus focus;
	ProductionFocusTask(ProductionEnums::ProductionFocus focus)
	{
		this->focus = focus;
	}
	std::string GetType(){return "UnitProductionTask";}
};