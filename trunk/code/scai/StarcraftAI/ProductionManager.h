#pragma once
#include <BWAPI.h>

class ProductionManager
{
public:
	ProductionManager(void);
private:
	BWAPI::Unit* GetSuitableSCV();
	void FollowBuildOrder();
	void BuildAccordingToThreats();
	void ProduceUnit();
	void BuildBuilding();
};
