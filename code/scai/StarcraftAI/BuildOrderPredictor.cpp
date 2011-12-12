#include "BuildOrderPredictor.h"


BuildOrderPredictor::BuildOrderPredictor()
{
}
void Update()
{

}
void BuildOrderPredictor::InitializePredictionNetwork(InformationEnums::Matchup matchup)
{
	
	if(matchup == InformationEnums::MatchupTvP)
	{
		predictionNetwork = BayesianNetwork("C:/tvpprediction.net");
	}
	else if(matchup == InformationEnums::MatchupTvT)
	{
		predictionNetwork = BayesianNetwork("C:/tvtprediction.net");
	}
	else if(matchup == InformationEnums::MatchupTvZ)
	{
		predictionNetwork = BayesianNetwork("C:/tvzprediction.net");
	}
	predictionNetwork.PrintNodes();
	float f = predictionNetwork.GetProbability("Barracks1","Seen");
	BWAPI::Broodwar->printf("%f",f);
	//UpdateTvTNetwork(BWAPI::UnitTypes::Terran_Barracks);
	//UpdateTvTNetwork(BWAPI::UnitTypes::Terran_Barracks);
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
void BuildOrderPredictor::UpdateTvPNetwork(BWAPI::UnitType building)
{

}
void BuildOrderPredictor::UpdateTvTNetwork(BWAPI::UnitType building)
{
	enemyBuildingsOwned[building]++;
	//DiscreteChanceNode* d = GetNodeAsDCN("Barracks1",&predictionNetwork);
	//d->selectState(0);
	if(building == BWAPI::UnitTypes::Terran_Barracks)
	{
		switch(enemyBuildingsOwned[building])
		{
			//case 1: ->selectState(0);break;
			//case 2: GetNodeAsDCN("Barracks2")->selectState(0);break;
		}
	}
	/*DiscreteChanceNode* build = GetNodeAsDCN("BuildChosen");
	build->generateTable();
	BWAPI::Broodwar->printf("The States are now: \n");
	for(int i = 0;i<build->getNumberOfStates();i++)
	{
		BWAPI::Broodwar->printf("State %s",build->getStateLabel(i).c_str());
	}*/
}
void BuildOrderPredictor::UpdateTvZNetwork(BWAPI::UnitType building)
{

}
DiscreteChanceNode* BuildOrderPredictor::GetNodeAsDCN(std::string name,Domain *domain)
{
	
	NodeList nodes = domain->getNodes();
	DiscreteChanceNode* returnNode;
	for (NodeList::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
		Node* node = *it;
		if(name == node->getName())
		{
			BWAPI::Broodwar->printf("name: %s",node->getLabel().c_str());
			returnNode = dynamic_cast<DiscreteChanceNode*>(node);
			break;
		}
	}
	return (returnNode);
}
