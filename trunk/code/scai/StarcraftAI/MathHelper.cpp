#include "MathHelper.h"
#include "math.h"
#define PI 3.14159265
struct MathHelper::ReturningUnit
{
	BWAPI::Unit* ClosestEnemy;
	bool exist;
};
BWAPI::Position MathHelper::GetPositionFromAngle(BWAPI::Position pos, int angle, int length)
{
	int xPos, yPos;
	double trueAngle = (double)angle*PI/180;
	
	double xCos = cos(trueAngle);
	double ySin = sin(trueAngle);
	xPos = pos.x()+(int)(xCos*(double)length);
	yPos = pos.y()+(int)(ySin*(double)length);

	BWAPI::Position newPos = BWAPI::Position(xPos,yPos);	
	return newPos;
}
std::list<BWAPI::Position> MathHelper::GetSurroundingPositions(BWAPI::Position pos, int tileSize)
{
	std::list<BWAPI::Position> positions;
	int angle = 0;
	//sqrt(double(tileSize^2+tileSize^2))
	int diagnonalLength = 68;

	positions.push_front(pos);

	for(int i = 0;i<8;i++)
	{	
		if(i%2 == 0)
		{
			positions.push_front(MathHelper::GetPositionFromAngle(pos, angle, tileSize));
		}
		else
		{
			positions.push_front(MathHelper::GetPositionFromAngle(pos, angle, diagnonalLength));
		}
		
		angle+=45;
	}
	return positions;
}

MathHelper::ReturningUnit MathHelper::GetNearestEnemy(BWAPI::Position unitPos)
{
	
	//BWAPI::Broodwar->printf("inside GetNerestEnemy");
	std::set<BWAPI::Player*> enemies = BWAPI::Broodwar->enemies();	
	std::set<BWAPI::Unit*> enemieUnits;
	ReturningUnit ClosestEnemyStruct;
	ClosestEnemyStruct.exist = false;

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
			//BWAPI::Broodwar->printf("enemy in range");
		}
	}

	//If there is any enemie units we know of.
	int distance = 30000;
	if(enemieUnits.empty() != true)
	{
		//BWAPI::Broodwar->printf("enemy not empty");
		//Calculating the distance to the nearest one,
		for(std::set<BWAPI::Unit*>::iterator k = enemieUnits.begin(); k != enemieUnits.end(); k++)
		{
			int getDist = (*k)->getDistance(unitPos);
			if(getDist < distance)
			{

				distance = getDist;
				ClosestEnemyStruct.ClosestEnemy = (*k);
				ClosestEnemyStruct.exist = true;
			}
		}
	}

	//ClosestEnemy->exists();
	return ClosestEnemyStruct;
}
int MathHelper::GetDistanceToNearestEnemy(BWAPI::Position pos)
{	
	//BWAPI::Broodwar->printf("inside GetDistanceToNearestEnemy / calling GetNerestEnemy");
	ReturningUnit ClosestEnemyStruct = GetNearestEnemy(pos);
	int distance = 30000;

	//If there is any enemie units we know of.
	if(ClosestEnemyStruct.exist == true)
	{
		int getDist = ClosestEnemyStruct.ClosestEnemy->getDistance(pos);
		distance = getDist;
	}
	else
	{
		distance = 0;
	}

	return distance;
}

double MathHelper::GetDistanceBetweenPositions(BWAPI::Position pos1, BWAPI::Position pos2)
{
	// Square root of (x2-x1)^2+(y2-y1)^2
	return sqrt(pow(double(pos2.x()-pos1.x()),2)+pow(double(pos2.y()-pos1.y()),2));
}
int MathHelper::GetDistanceToNearestAlly(BWAPI::Position pos, int unitID)
{
	//Getting a list of all our units.
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	int distance = 30000;

	//Iterating trough them, and calculating the distance to the closest one
	for(std::set<BWAPI::Unit*>::const_iterator i = myUnits.begin(); i != myUnits.end(); i++)
	{
		if((*i)->getID() != unitID && (*i)->getType().isBuilding() == false && (*i)->exists())
		{
			int getDist = (*i)->getDistance(pos);
			if(getDist < distance)
			{
				distance = getDist;
			}
		}
	}
	//BWAPI::Broodwar->printf("distance = %d. from %d,%d to", distance,x,y);
	if(distance == 30000)
		return 0;
	else
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
		if((*i)->exists())
		{
			n++;
			BWAPI::Position unitPos = (*i)->getPosition();
			x += (mass*unitPos.x());
		}
	}
	x = x/(n*mass);

	for(std::set<BWAPI::Unit*>::const_iterator j = listOfUnits.begin(); j != listOfUnits.end(); j++)
	{
		if((*j)->exists())
		{
			BWAPI::Position unitPos = (*j)->getPosition();
			y += (mass*unitPos.y());
		}
	}
	y = y/(n*mass);

	//Center is now calculated
	
	return BWAPI::Position(x,y);
}
