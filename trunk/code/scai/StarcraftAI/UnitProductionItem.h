#pragma once

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
