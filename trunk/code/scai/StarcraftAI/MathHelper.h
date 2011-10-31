#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class MathHelper
{
public:
	static std::list<BWAPI::Position> GetSurroundingPositions(int x, int y, int tileSize);
	static BWAPI::Position GetPositionFromAngle(int x, int y, int angle, int length);
	static int GetNearestEnemy(int x, int y);
	static int GetNearestAlly(int x, int y);
	static void GetSquadCenter(std::list<BWAPI::Unit*>, int &x, int &y);
};
