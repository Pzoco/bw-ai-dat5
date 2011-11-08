#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class MathHelper
{
public:
	static std::list<BWAPI::Position> GetSurroundingPositions(int x, int y, int tileSize);
	static BWAPI::Position GetPositionFromAngle(int x, int y, int angle, int length);
	static int GetNearestEnemy(BWAPI::Position Pos,  BWAPI::Position centerPos);
	static int GetNearestAlly(int x, int y, int unitID);
	static void GetSquadCenter(std::set<BWAPI::Unit*> listOfUnits, int &x, int &y);
};
