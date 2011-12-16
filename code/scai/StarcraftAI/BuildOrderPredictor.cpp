#include "BuildOrderPredictor.h"


BuildOrderPredictor::BuildOrderPredictor()
{
}
void BuildOrderPredictor::InitializePredictionNetwork(InformationEnums::Matchup matchup)
{
	
	if(matchup == InformationEnums::MatchupTvP)
	{
		predictionNetwork = BayesianNetwork("C:/tvpprediction.net");
		protossOpeningDone = false;
		predictionNetwork.EnterEvidence("Assimilator","NotSeen");
	}
	else if(matchup == InformationEnums::MatchupTvT)
	{
		predictionNetwork = BayesianNetwork("C:/tvtprediction.net");
	}
	else if(matchup == InformationEnums::MatchupTvZ)
	{
		predictionNetwork = BayesianNetwork("C:/tvzpredictionthreat.net");
	}
	BuildOrderPredictor::matchup = matchup;
}

InformationEnums::ThreatLevel BuildOrderPredictor::GetCurrentThreatLevel()
{
	//Get the current time and current most probable build
	std::string currentTime = "";
	int timeInSeconds = BWAPI::Broodwar->elapsedTime();
	if(timeInSeconds < 359){currentTime="ZerotoFivemin";}
	else if(timeInSeconds > 360 && timeInSeconds < 539){currentTime="SixtoEightmin";}
	else if(timeInSeconds > 539){currentTime="NinetoElevenmin";}
	BWAPI::Broodwar->printf("Time is %d",timeInSeconds);
	BWAPI::Broodwar->printf("Time is %s",currentTime.c_str());
	//Enter the evidence of the current most probable build and the current time
	predictionNetwork.EnterEvidence("Time",currentTime);
	std::string threatLevel = predictionNetwork.GetMostProbableState("ThreatLevel");

	//Convert the string to an enum
	InformationEnums::ThreatLevel currentThreatLevel;
	if(threatLevel == "Low"){currentThreatLevel = InformationEnums::ThreatLow;}
	else if(threatLevel == "Medium"){currentThreatLevel = InformationEnums::ThreatMedium;}
	else if(threatLevel == "High"){currentThreatLevel = InformationEnums::ThreatHigh;}
	
	predictionNetwork.PrintMostProbableState("ThreatLevel");
	//Retract the evidence of the build and time as this might change
	predictionNetwork.RetractEvidence("Time");
	

	return currentThreatLevel;
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
	
}
void BuildOrderPredictor::UpdatePredictionNetwork(BWAPI::UpgradeType upgrade)
{
	if(matchup == InformationEnums::MatchupTvP)
	{
		if(upgrade == BWAPI::UpgradeTypes::Singularity_Charge)
		{
			predictionNetwork.EnterEvidence("DragoonRange","Seen");
			if(!protossOpeningDone)
			{
				BWAPI::Broodwar->printf("Updated the prediction network");
				predictionNetwork.PrintMostProbableState("Opening");
			}
		}
	}
	
}
void BuildOrderPredictor::UpdateTvPNetwork(BWAPI::UnitType building)
{
	if(building == BWAPI::UnitTypes::Protoss_Gateway && 
		(enemyBuildingsOwned[building]==1 || enemyBuildingsOwned[building]==2))
	{
		char buffer [2];
		std::string nodeNumber = itoa(enemyBuildingsOwned[building],buffer,10);
		predictionNetwork.EnterEvidence(("Gateway"+nodeNumber),"Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		if(protossOpeningDone)
			predictionNetwork.PrintMostProbableState("BuildChosen");
		else
			predictionNetwork.PrintMostProbableState("Opening");
	}
	else if((building == BWAPI::UnitTypes::Protoss_Robotics_Facility) && enemyBuildingsOwned[building]==1)
	{ 
		predictionNetwork.EnterEvidence("RoboticsFacility","Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		if(!protossOpeningDone)
			predictionNetwork.PrintMostProbableState("Opening");	
	}
	else if(building == BWAPI::UnitTypes::Protoss_Nexus && enemyBuildingsOwned[building]==2)
	{
		predictionNetwork.EnterEvidence("Nexus2","Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		if(!protossOpeningDone)
			predictionNetwork.PrintMostProbableState("Opening");			
	}
	else if((building == BWAPI::UnitTypes::Protoss_Fleet_Beacon || 
			building == BWAPI::UnitTypes::Protoss_Stargate || 
			building == BWAPI::UnitTypes::Protoss_Observatory)&& 
			enemyBuildingsOwned[building]==1)
	{
		std::string nodeName = building.getName();
		nodeName.erase(0,8);
		std::remove(nodeName.begin(), nodeName.end(), ' ');
		char buffer [2];
		std::string nodeNumber = itoa(enemyBuildingsOwned[building],buffer,10);
		predictionNetwork.EnterEvidence((nodeName),"Seen");
		protossOpeningDone=true;
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");

	}
	else if(building == BWAPI::UnitTypes::Protoss_Assimilator)
	{
		predictionNetwork.EnterEvidence("Assimilator","Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("Opening");
	}
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
		predictionNetwork.EnterEvidence((nodeName+nodeNumber),"Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");
		predictionNetwork.PrintNodes();
	}
	else if((building == BWAPI::UnitTypes::Terran_Barracks || 
			building == BWAPI::UnitTypes::Terran_Factory) &&
			enemyBuildingsOwned[building]==2)
	{
		//Converts the building type to how the nodes are written
		std::string nodeName = building.getName();
		nodeName.erase(0,7);
		std::remove(nodeName.begin(), nodeName.end(), ' ');
		char buffer [2];
		std::string nodeNumber = itoa(2,buffer,10);
		predictionNetwork.EnterEvidence((nodeName+nodeNumber),"Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");
	}
	else if(building == BWAPI::UnitTypes::Terran_Command_Center &&
			enemyBuildingsOwned[building]==2)
	{
		predictionNetwork.EnterEvidence("CommandCenter2","Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");
	}

}
void BuildOrderPredictor::UpdateTvZNetwork(BWAPI::UnitType building)
{
	if(building == BWAPI::UnitTypes::Zerg_Hatchery && 
		(enemyBuildingsOwned[building]==2 || enemyBuildingsOwned[building]==3))
	{
		char buffer [2];
		std::string nodeNumber = itoa(enemyBuildingsOwned[building],buffer,10);
		predictionNetwork.EnterEvidence(("Hatchery"+nodeNumber),"Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");
		GetCurrentThreatLevel();
	}
	else if(building == BWAPI::UnitTypes::Zerg_Spire && 
			enemyBuildingsOwned[building]==1)
	{
		predictionNetwork.EnterEvidence("Spire","Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");
		GetCurrentThreatLevel();
	}
	else if(building == BWAPI::UnitTypes::Zerg_Hydralisk_Den &&
			enemyBuildingsOwned[building]==1)
	{
		predictionNetwork.EnterEvidence("HydraliskDen","Seen");
		BWAPI::Broodwar->printf("Updated the prediction network");
		predictionNetwork.PrintMostProbableState("BuildChosen");
		GetCurrentThreatLevel();
	}
}