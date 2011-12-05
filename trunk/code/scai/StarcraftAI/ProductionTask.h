#pragma once
#include <BWAPI.h>
#include "ProductionEnums.h"

class ProductionTask
{
public:
	int mineralPrice;
	int gasPrice;
	virtual std::string GetType();
protected:
	BWAPI::UnitType requiredBuilding;
};





