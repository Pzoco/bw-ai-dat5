#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class MathHelper
{
public:
	static std::list<BWAPI::Position> GetSurroundingPositions(int x, int y, int tileSize);
	static BWAPI::Position GetPositionFromAngle(int x, int y, int angle, int length);
	static int GetDistanceToNearestEnemy(BWAPI::Position pos,  BWAPI::Position centerPos);
	static int GetDistanceToNearestAlly(BWAPI::Position pos, int unitID);
	static BWAPI::Position GetSquadCenterPosition(std::set<BWAPI::Unit*> listOfUnits);
};
