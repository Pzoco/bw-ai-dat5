#include "StrategyManager.h"

StrategyManager* StrategyManager::strategyManager = 0;

StrategyManager* StrategyManager::GetInstance()
{
	if(strategyManager == 0)
	{
		strategyManager = new StrategyManager();
	}
	return strategyManager;
}
StrategyManager::StrategyManager(void)
{
}
