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

int MathHelper::GetNearestEnemy(int x, int y)
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
	if(enemieUnits.empty() != true)
	{
		//Calculating the distance to the nearest one,
		for(std::set<BWAPI::Unit*>::iterator k = enemieUnits.begin(); k != enemieUnits.end(); k++)
		{
			int getDist = (*k)->getDistance(BWAPI::Position(x,y));
			if(getDist < distance)
			{
				distance = getDist;
			}
		}
	}

	return distance;
}
int MathHelper::GetNearestAlly(int x, int y)
{
	//Getting a list of all our units.
	std::set<BWAPI::Unit*> myUnits = BWAPI::Broodwar->self()->getUnits();
	int distance = 30000;

	//Iterating trough them, and calculating the distance to the closest one
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
//This function takes int &x, int &y not to use it as input but to allow to return to values ;)
void MathHelper::GetSquadCenter(std::list<BWAPI::Unit*>, int &x, int &y)
{
	
	return;
}