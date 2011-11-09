#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class MathHelper
{
public:
	virtual struct ReturningUnit;
	static std::list<BWAPI::Position> GetSurroundingPositions(BWAPI::Position pos, int tileSize);
	static BWAPI::Position GetPositionFromAngle(BWAPI::Position pos, int angle, int length);
	static int GetDistanceToNearestEnemy(BWAPI::Position pos);
	static ReturningUnit GetNerestEnemy(BWAPI::Position unitPos);
	static int GetDistanceToNearestAlly(BWAPI::Position pos, int unitID);
	static BWAPI::Position GetSquadCenterPosition(std::set<BWAPI::Unit*> listOfUnits);
};
