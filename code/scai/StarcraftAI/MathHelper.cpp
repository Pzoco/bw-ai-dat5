#include "MathHelper.h"
#include "math.h"
#define PI 3.14159265

BWAPI::Position MathHelper::GetPositionFromAngle(int x, int y, int angle, int length)
{
	int xPos, yPos;
	//xPos = x+((int)cos((float)angle))*length;
	//yPos = y+((int)sin((float)angle))*length;
	double trueAngle = (double)angle*PI/180;
	
	double xCos = cos(trueAngle);
	double ySin = sin(trueAngle);
	xPos = x+(int)(xCos*(double)length);
	yPos = y+(int)(ySin*(double)length);

	BWAPI::Position newPos = BWAPI::Position(xPos,yPos);
	//BWAPI::Broodwar->printf("pos %d,%d - tile %d,%d",x,y,newPos.x(),newPos.y());
	//BWAPI::Broodwar->printf("input: pos=%d,%d - a = %d - l = %d",x,y,angle,length);
	//BWAPI::Broodwar->printf("GetPositionFromAngle: pos=%d,%d - tile=%d,%d",xPos,yPos,newPos.x(),newPos.y());
	
	return newPos;
}
std::list<BWAPI::Position> MathHelper::GetSurroundingPositions(int x, int y, int tileSize)
{
	std::list<BWAPI::Position> positions;
	int angle = 0;
	//sqrt(double(tileSize^2+tileSize^2))
	int diagnonalLength = 68;

	positions.push_front(BWAPI::Position(x,y));

	for(int i = 0;i<8;i++)
	{	
		if(i%2 == 0)
		{
			positions.push_front(MathHelper::GetPositionFromAngle(x, y, angle, tileSize));
		}
		else
		{
			positions.push_front(MathHelper::GetPositionFromAngle(x, y, angle, diagnonalLength));
		}
		
		angle+=45;
	}
	return positions;
}

int MathHelper::GetDistanceToNearestEnemy(BWAPI::Position pos, BWAPI::Position centerPos)
{
	std::set<BWAPI::Player*> enemies = BWAPI::Broodwar->enemies();	
	std::set<BWAPI::Unit*> enemieUnits;
	int distance = 30000;

	//Now to get all the enemies units in one list.
	//Iterating trough all the enemies
	for(std::set<BWAPI::Player*>::const_iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		//Making a list of that players units
		std::set<BWAPI::Unit*> tempUnits = (*i)->getUnits();

		//Iterating trough them.
		for(std::set<BWAPI::Unit*>::iterator j = tempUnits.begin(); j != tempUnits.end(); j++)
		{
			//And add them to a list of all enemieunits in the map.
			enemieUnits.insert((*j));
		}
	}

	//If there is any enemie units we know of.
	int rangeModifyer = 0;
	if(enemieUnits.empty() != true)
	{
		//Calculating the distance to the nearest one,
		for(std::set<BWAPI::Unit*>::iterator k = enemieUnits.begin(); k != enemieUnits.end(); k++)
		{
			int getDist = (*k)->getDistance(pos);
			int distFromCenter = (*k)->getDistance(centerPos);
			if(getDist < distance)
			{
				rangeModifyer = distFromCenter;
				distance = getDist;
			}
		}
		distance = (rangeModifyer - distance + rangeModifyer);
	}
	else
	{
		distance = 0;
	}

	return distance;
}
int MathHelper::GetDistanceToNearestAlly(BWAPI::Position pos, int unitID)
{
	//Getting a list of all our units.
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	int distance = 30000;

	//Iterating trough them, and calculating the distance to the closest one
	for(std::set<BWAPI::Unit*>::const_iterator i = myUnits.begin(); i != myUnits.end(); i++)
	{
		if((*i)->getID() != unitID && (*i)->getType().isBuilding() == false)
		{
			int getDist = (*i)->getDistance(pos);
			if(getDist < distance)
			{
				distance = getDist;
			}
		}
	}
	//BWAPI::Broodwar->printf("distance = %d. from %d,%d to", distance,x,y);
	return distance;
}

//This function takes a list of units and returns the center of the squad ;)
BWAPI::Position MathHelper::GetSquadCenterPosition(std::set<BWAPI::Unit*> listOfUnits)
{
	/*
		Center of mass from http://klassewiki.dk/OTG3B/index.php/1._September,_Fysik
		xG = (m1*x1 + m2*x2 .. mi*xi)/(m1+m2+...mi)

		yG = (m1*y1 + m2*y2 .. mi*yi)/(m1+m2+...mi)

		for now all units have the same mass (equaly importent).
	*/
	int mass = 1;
	int n = 0;
	int x = 0;
	int y = 0;
	for(std::set<BWAPI::Unit*>::const_iterator i = listOfUnits.begin(); i != listOfUnits.end(); i++)
	{
		n++;
		BWAPI::Position unitPos = (*i)->getPosition();
		x += (mass*unitPos.x());
	}
	x = x/(n*mass);

	for(std::set<BWAPI::Unit*>::const_iterator j = listOfUnits.begin(); j != listOfUnits.end(); j++)
	{
		BWAPI::Position unitPos = (*j)->getPosition();
		y += (mass*unitPos.y());
	}
	y = y/(n*mass);

	//Center is now calculated
	
	return BWAPI::Position(x,y);
}