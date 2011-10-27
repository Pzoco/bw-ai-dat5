#include "MathHelper.h"
#include "math.h"

BWAPI::Position MathHelper::GetPositionFromAngle(int x, int y, int angle, int length)
{
	int xPos, yPos;
	xPos = x+((int)cos((float)angle))*length;
	yPos = y+((int)sin((float)angle))*length;
	
	return BWAPI::Position(xPos,yPos);
}
std::list<BWAPI::Position> MathHelper::GetSurroundingPositions(int x, int y, int tileSize)
{
	std::list<BWAPI::Position> positions;
	int angle = 0;
	double diagnonalLength = sqrt(double(tileSize^2+tileSize^2));

	for(int i = 0;i<8;i++)
	{	
		if(i%2 == 0)
		{
			positions.push_front(MathHelper::GetPositionFromAngle(x, y, angle, tileSize));
		}
		else
		{
			positions.push_front(MathHelper::GetPositionFromAngle(x, y, angle, (int)diagnonalLength));
		}
		
		angle+=45;
	}
	return positions;
}

void MathHelper::GetNearestEnemy(int x, int y)
{
	std::set<BWAPI::Player*> enemies = BWAPI::Broodwar->enemies();

}
int MathHelper::GetNearestAlly(int x, int y)
{
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	int distance = 30000;
	for(std::set<BWAPI::Unit*>::const_iterator i = myUnits.begin(); i != myUnits.end(); i++)
	{
		int getDist = (*i)->getDistance(BWAPI::Position(x,y));
		if(getDist < distance)
		{
			distance = getDist;
		}
	}
	return distance;
}