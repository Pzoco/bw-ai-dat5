#include "BuildOrderPredictor.h"


BuildOrderPredictor::BuildOrderPredictor()
{
}
void BuildOrderPredictor::InitializePredictionNetwork(InformationEnums::Matchup matchup)
{
	
	if(matchup == InformationEnums::MatchupTvP)
	{
		predictionNetwork = new BayesianNetwork("C:/tvpprediction.net");
	}
	else if(matchup == InformationEnums::MatchupTvT)
	{
		predictionNetwork = new BayesianNetwork("C:/tvtprediction.net");
	}
	else if(matchup == InformationEnums::MatchupTvZ)
	{
		predictionNetwork = new BayesianNetwork("C:/tvzprediction.net");
	}
	BuildOrderPredictor::matchup = matchup;
}

void BuildOrderPredictor::UpdatePredictionNetwork(BWAPI::UnitType building)
{
	enemyBuildingsOwned[building]++;
	if(matchup == InformationEnums::MatchupTvP)
		UpdateTvPNetwork(building);
	else if(matchup == InformationEnums::MatchupTvT)
		UpdateTvTNetwork(building);
	else if(matchup == InformationEnums::MatchupTvZ)
		UpdateTvZNetwork(building);
	
	predictionNetwork->PrintMostProbableState("BuildChosen");
}
void BuildOrderPredictor::UpdateTvPNetwork(BWAPI::UnitType building)
{
	
}
void BuildOrderPredictor::UpdateTvTNetwork(BWAPI::UnitType building)
{
	if((building == BWAPI::UnitTypes::Terran_Academy || 
			building == BWAPI::UnitTypes::Terran_Starport ||
			building == BWAPI::UnitTypes::Terran_Barracks ||
			building == BWAPI::UnitTypes::Terran_Factory)&& 
			enemyBuildingsOwned[building]==1)
	{
		//Converts the building type to how the nodes are written
		std::string nodeName = building.getName();
		nodeName.erase(0,7);
		std::remove(nodeName.begin(), nodeName.end(), ' ');
		char buffer [2];
		std::string nodeNumber = itoa(1,buffer,10);	
		predictionNetwork->EnterEvidence((nodeName+nodeNumber),"Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
	}
	else if((building == BWAPI::UnitTypes::Terran_Barracks ||
			building == BWAPI::UnitTypes::Terran_Command_Center || 
			building == BWAPI::UnitTypes::Terran_Factory) &&
			enemyBuildingsOwned[building]==2)
	{
		//Converts the building type to how the nodes are written
		std::string nodeName = building.getName();
		nodeName.erase(0,7);
		std::remove(nodeName.begin(), nodeName.end(), ' ');
		char buffer [2];
		std::string nodeNumber = itoa(2,buffer,10);
		predictionNetwork->EnterEvidence((nodeName+nodeNumber),"Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
	}

}
void BuildOrderPredictor::UpdateTvZNetwork(BWAPI::UnitType building)
{
	if(building == BWAPI::UnitTypes::Zerg_Hatchery && 
		(enemyBuildingsOwned[building]==2 || enemyBuildingsOwned[building]==3))
	{
		std::string nodeName = building.getName();
		nodeName.erase(0,5);
		std::remove(nodeName.begin(), nodeName.end(), ' ');
		char buffer [2];
		std::string nodeNumber = itoa(enemyBuildingsOwned[building],buffer,10);
		predictionNetwork->EnterEvidence((nodeName+nodeNumber),"Seen");
	}
	else if(building == BWAPI::UnitTypes::Zerg_Spire && 
			building == BWAPI::UnitTypes::Zerg_Hydralisk_Den &&
			enemyBuildingsOwned[building]==1)
	{
		std::string nodeName = building.getName();
		std::remove(nodeName.begin(), nodeName.end(), ' ');
		nodeName.erase(0,3);
		predictionNetwork->EnterEvidence((nodeName),"Seen");
	}
}