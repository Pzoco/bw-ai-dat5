#pragma once
#include <BWAPI.h>
#include "ProductionTask.h"

class ProductionFocusTask: public ProductionTask
{
public:
	ProductionEnums::ProductionFocus focus;
	ProductionFocusTask(ProductionEnums::ProductionFocus focus);
	std::string GetType();
};