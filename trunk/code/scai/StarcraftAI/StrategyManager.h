#pragma once

class StrategyManager
{
public:
	static StrategyManager* GetInstance();
private:
	StrategyManager(void);
	static StrategyManager* strategyManager;
};
