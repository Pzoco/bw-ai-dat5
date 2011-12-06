#pragma once
#include <BWAPI.h>
#include <BWTA.h>
class MathHelper
{
public:
	virtual struct ReturningUnit;
	static bool MathHelper::IsTileValid(BWAPI::Position unitPos, BWAPI::Position pos, std::set<BWAPI::Unit*> mySquad);
	static std::list<BWAPI::Position> GetSurroundingPositions(BWAPI::Position pos, int tileSize);
	static BWAPI::Position GetPositionFromAngle(BWAPI::Position pos, int angle, int length);
	static int GetDistanceToNearestEnemy(BWAPI::Position pos);
	static double GetDistanceBetweenPositions(BWAPI::Position pos1, BWAPI::Position pos2);
	static ReturningUnit GetNearestEnemy(BWAPI::Position unitPos);
	static int GetDistanceToNearestAlly(BWAPI::Position pos, int unitID);
	static BWAPI::Position GetSquadCenterPosition(std::set<BWAPI::Unit*> listOfUnits);
	static BWAPI::Position CalculateNextTileInLine(BWAPI::Position currentPos, BWAPI::Position targetPos);
};
