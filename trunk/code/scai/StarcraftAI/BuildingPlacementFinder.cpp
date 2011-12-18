#include "BuildingPlacementFinder.h"
#include <BWAPI.h>
#include "WorkerManager.h"
using namespace BWAPI;
BuildingPlacementFinder::BuildingPlacementFinder()
{
	initialized =false;
}


BWAPI::TilePosition BuildingPlacementFinder::FindBuildLocation(BWAPI::UnitType buildingType, ProductionEnums::BuildingPlacement buildingPlacement)
{
	if(!initialized)
	{
		SaveBarracksPositions();
		myBaseTile = Broodwar->self()->getStartLocation();
		myBasePosition = Position(myBaseTile);
		if( myBaseTile.x() >= Broodwar->mapWidth()/2  && myBaseTile.y() < Broodwar->mapWidth()/2)
		{
			myBaseEnum=InformationEnums::NE;
		}
		if( myBaseTile.x() >= Broodwar->mapWidth()/2  && myBaseTile.y() >= Broodwar->mapWidth()/2)
		{
			myBaseEnum=InformationEnums::SE;
		}
		if( myBaseTile.x() < Broodwar->mapWidth()/2  && myBaseTile.y() >= Broodwar->mapWidth()/2)
		{
			myBaseEnum=InformationEnums::SW;
		}
		if( myBaseTile.x() < Broodwar->mapWidth()/2  && myBaseTile.y() < Broodwar->mapWidth()/2)
		{
			myBaseEnum=InformationEnums::NW;
		}

		for(int i=0;i<BASE_TILES;i++)
		{
			for(int j=0;j<BASE_TILES;j++)
			{

			}
		}
		initialized =true;
		//Broodwar->printf("Building Placement initialized");
	}

	if(buildingType == BWAPI::UnitTypes::Terran_Refinery)
	{
		return GetClosestGasGeyser(BWAPI::Broodwar->self()->getStartLocation());
	}
	if(buildingPositions[buildingType].size() > 0)
	{
		for each(TilePosition position in buildingPositions[buildingType])
		{
			if(canBuildHere(position,buildingType))
			{
				BWAPI::TilePosition returnPosition = position;
				buildingPositions[buildingType].remove(position);
				return returnPosition;
			}
		}
	}
	else
	{
		return getBuildLocationNear(BWAPI::Broodwar->self()->getStartLocation(),buildingType);
	}
	return BWAPI::TilePositions::None;
}

bool BuildingPlacementFinder::canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const
{
	//returns true if we can build this type of unit here. Takes into account reserved tiles.
	if (!BWAPI::Broodwar->canBuildHere(NULL, position, type))
		return false;
	//  for(int x = position.x(); x < position.x() + type.tileWidth(); x++)
	//    for(int y = position.y(); y < position.y() + type.tileHeight(); y++)
	//      if (reserveMap[x][y])
	//        return false;
	return true;
}
bool BuildingPlacementFinder::canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const
{
	return canBuildHereWithSpace(position,type,this->buildDistance);
}

bool BuildingPlacementFinder::canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const
{
	//returns true if we can build this type of unit here with the specified amount of space.
	//space value is stored in this->buildDistance.

	//if we can't build here, we of course can't build here with space
	if (!this->canBuildHere(position, type))
		return false;

	int width=type.tileWidth();
	int height=type.tileHeight();

	//make sure we leave space for add-ons. These types of units can have addons:
	if (type==BWAPI::UnitTypes::Terran_Command_Center ||
		type==BWAPI::UnitTypes::Terran_Factory || 
		type==BWAPI::UnitTypes::Terran_Starport ||
		type==BWAPI::UnitTypes::Terran_Science_Facility)
	{
		width+=2;
	}
	int startx = position.x() - buildDist;
	if (startx<0) return false;
	int starty = position.y() - buildDist;
	if (starty<0) return false;
	int endx = position.x() + width + buildDist;
	if (endx>BWAPI::Broodwar->mapWidth()) return false;
	int endy = position.y() + height + buildDist;
	if (endy>BWAPI::Broodwar->mapHeight()) return false;

	if (position.x()>3)
	{
		int startx2=startx-2;
		if (startx2<0) startx2=0;
		for(int x = startx2; x < startx; x++)
		{
			for(int y = starty; y < endy; y++)
			{
				std::set<BWAPI::Unit*> units = BWAPI::Broodwar->getUnitsOnTile(x, y);
				for(std::set<BWAPI::Unit*>::iterator i = units.begin(); i != units.end(); i++)
				{
					if (!(*i)->isLifted())
					{
						BWAPI::UnitType type=(*i)->getType();
						if (type==BWAPI::UnitTypes::Terran_Command_Center ||
							type==BWAPI::UnitTypes::Terran_Factory || 
							type==BWAPI::UnitTypes::Terran_Starport ||
							type==BWAPI::UnitTypes::Terran_Science_Facility)
						{
							return false;
						}
					}
				}
			}
		}
	}


	return true;
}

BWAPI::TilePosition BuildingPlacementFinder::getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type) const
{
	return getBuildLocationNear(position, type,this->buildDistance);
}

BWAPI::TilePosition BuildingPlacementFinder::getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const
{
	//returns a valid build location near the specified tile position.
	//searches outward in a spiral.
	int x      = position.x();
	int y      = position.y();
	int length = 1;
	int j      = 0;
	bool first = true;
	int dx     = 0;
	int dy     = 1;
	while (length < BWAPI::Broodwar->mapWidth()) //We'll ride the spiral to the end
	{
		//if we can build here, return this tile position
		if (x >= 0 && x < BWAPI::Broodwar->mapWidth() && y >= 0 && y < BWAPI::Broodwar->mapHeight())
			if (this->canBuildHereWithSpace(BWAPI::TilePosition(x, y), type, buildDist))
				return BWAPI::TilePosition(x, y);

		//otherwise, move to another position
		x = x + dx;
		y = y + dy;
		//count how many steps we take in this direction
		j++;
		if (j == length) //if we've reached the end, its time to turn
		{
			//reset step counter
			j = 0;

			//Spiral out. Keep going.
			if (!first)
				length++; //increment step counter if needed

			//first=true for every other turn so we spiral out at the right rate
			first =! first;

			//turn counter clockwise 90 degrees:
			if (dx == 0)
			{
				dx = dy;
				dy = 0;
			}
			else
			{
				dy = -dx;
				dx = 0;
			}
		}
		//Spiral out. Keep going.
	}
	return BWAPI::TilePositions::None;
}


BWAPI::TilePosition BuildingPlacementFinder::GetClosestGasGeyser(BWAPI::TilePosition position)
{
	BWAPI::TilePosition closestGeyser;
	double bestDistance = 10000;
	for(std::set<BWAPI::Unit*>::iterator g=BWAPI::Broodwar->getGeysers().begin();g!=BWAPI::Broodwar->getGeysers().end();g++)
	{
		if((*g)->isVisible())
		{
			double distanceToGeyser = position.getDistance((*g)->getTilePosition());
			if(distanceToGeyser < bestDistance)
			{
				closestGeyser = (*g)->getTilePosition();
				bestDistance = distanceToGeyser;
			}
		}
	}
	return closestGeyser;
}

void BuildingPlacementFinder::SaveBarracksPositions()
{
	//returns a valid build location near the specified tile position.
	//searches outward in a spiral.
	int x      = BWAPI::Broodwar->self()->getStartLocation().x();
	int y      = BWAPI::Broodwar->self()->getStartLocation().y();
	int length = 1;
	int j      = 0;
	bool first = true;
	int dx     = 0;
	int dy     = 1;
	BWAPI::UnitType barracks = BWAPI::UnitTypes::Terran_Barracks;
	while (length < BWAPI::Broodwar->mapWidth()) //We'll ride the spiral to the end
	{
		//if we can build here, return this tile position
		if (x >= 0 && x < BWAPI::Broodwar->mapWidth() && y >= 0 && y < BWAPI::Broodwar->mapHeight())
			if (this->canBuildHereWithSpace(BWAPI::TilePosition(x, y), barracks, buildDistance))
				if(canBuildHere(BWAPI::TilePosition(x,y+barracks.tileHeight()),barracks) &&
					canBuildHere(BWAPI::TilePosition(x+barracks.tileWidth(),y),barracks) && 
					canBuildHere(BWAPI::TilePosition(x+barracks.tileWidth(),y+barracks.tileHeight()),barracks))
				{
					buildingPositions[barracks].push_back(TilePosition(x,y));
					buildingPositions[barracks].push_back(TilePosition(x,y+barracks.tileHeight()));
					buildingPositions[barracks].push_back(TilePosition(x+barracks.tileWidth(),y));
					buildingPositions[barracks].push_back(TilePosition(x+barracks.tileWidth(),y+barracks.tileHeight()));
					break;
				}

				//otherwise, move to another position
				x = x + dx;
				y = y + dy;
				//count how many steps we take in this direction
				j++;
				if (j == length) //if we've reached the end, its time to turn
				{
					//reset step counter
					j = 0;

					//Spiral out. Keep going.
					if (!first)
						length++; //increment step counter if needed

					//first=true for every other turn so we spiral out at the right rate
					first =! first;

					//turn counter clockwise 90 degrees:
					if (dx == 0)
					{
						dx = dy;
						dy = 0;
					}
					else
					{
						dy = -dx;
						dx = 0;
					}
				}
				//Spiral out. Keep going.
	}
}
void BuildingPlacementFinder::SaveFactoriesPositions()
{
	//returns a valid build location near the specified tile position.
	//searches outward in a spiral.
	int x      = BWAPI::Broodwar->self()->getStartLocation().x();
	int y      = BWAPI::Broodwar->self()->getStartLocation().y();
	int length = 1;
	int j      = 0;
	bool first = true;
	int dx     = 0;
	int dy     = 1;
	BWAPI::UnitType factory = BWAPI::UnitTypes::Terran_Factory;
	while (length < BWAPI::Broodwar->mapWidth()) //We'll ride the spiral to the end
	{
		//if we can build here, return this tile position
		if (x >= 0 && x < BWAPI::Broodwar->mapWidth() && y >= 0 && y < BWAPI::Broodwar->mapHeight())
			if (this->canBuildHereWithSpace(BWAPI::TilePosition(x, y), factory, buildDistance))
				if(canBuildHere(BWAPI::TilePosition(x,y+factory.tileHeight()),factory) &&
					canBuildHere(BWAPI::TilePosition(x-factory.tileWidth(),y),factory) && 
					canBuildHere(BWAPI::TilePosition(x-factory.tileWidth(),y+factory.tileHeight()),factory))
				{
					buildingPositions[factory].push_back(TilePosition(x,y));
					buildingPositions[factory].push_back(TilePosition(x,y+factory.tileHeight()));
					buildingPositions[factory].push_back(TilePosition(x-factory.tileWidth(),y));
					buildingPositions[factory].push_back(TilePosition(x-factory.tileWidth(),y+factory.tileHeight()));
					if(!OverlapInBuildingPlacement(factory,UnitTypes::Terran_Barracks))
						break;
					buildingPositions[factory].clear();
				}

				//otherwise, move to another position
				x = x + dx;
				y = y + dy;
				//count how many steps we take in this direction
				j++;
				if (j == length) //if we've reached the end, its time to turn
				{
					//reset step counter
					j = 0;

					//Spiral out. Keep going.
					if (!first)
						length++; //increment step counter if needed

					//first=true for every other turn so we spiral out at the right rate
					first =! first;

					//turn counter clockwise 90 degrees:
					if (dx == 0)
					{
						dx = dy;
						dy = 0;
					}
					else
					{
						dy = -dx;
						dx = 0;
					}
				}
				//Spiral out. Keep going.
	}
}
bool BuildingPlacementFinder::OverlapInBuildingPlacement(BWAPI::UnitType type1, BWAPI::UnitType type2)
{
	for each(TilePosition pos1 in buildingPositions[type1])
	{
		for each(TilePosition pos2 in buildingPositions[type2])
		{
			for(int x=0;x<pos2.x()+type2.tileWidth();x++)
			{
				for(int y=0;y<pos2.y()+type2.tileHeight();y++)
				{
					if((x<pos1.x()+type1.tileWidth() && x>pos1.x()) ||
						(y<pos1.y()+type1.tileHeight() && y>pos1.y()))
					{
						return true;
					}	
				}
			}
		}
	}
	return false;
}