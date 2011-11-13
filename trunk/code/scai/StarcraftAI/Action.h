#pragma once
#include "State.h"
class Action
{
public:
	State state;
	double expectedReward;
	double actualReward;
	Action(void);
};
