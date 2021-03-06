#include "BayesianNetwork.h"

BayesianNetwork::BayesianNetwork(){}
BayesianNetwork::BayesianNetwork(std::string fileName)
{
	domain = new Domain(fileName,NULL);
}
float BayesianNetwork::GetProbability(std::string nodeName,std::string stateName)
{
	Domain * compileDomain = new Domain(domain);
	compileDomain->compile();
	NodeList nodes = compileDomain->getNodes();
	DiscreteChanceNode* probabilityNode;
	for (NodeList::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		Node* node = *it;
		if(nodeName == node->getName())
		{
			probabilityNode = dynamic_cast<DiscreteChanceNode*>(node);
			size_t index = probabilityNode->getStateIndex(stateName);
			return (float)probabilityNode->getBelief(index);	
		}
	}
	BWAPI::Broodwar->printf("Node %s not found",nodeName);
	return 0.0;
}
std::string BayesianNetwork::GetMostProbableState(std::string nodeName)
{
	float highest = 0.0;
	std::string stateName = "";
	DiscreteChanceNode* node = dynamic_cast<DiscreteChanceNode*>(domain->getNodeByName(nodeName));
	for(int i =0;i<(int)node->getNumberOfStates();i++)
	{
		if((float)node->getBelief(i) > highest)
		{
			stateName = node->getStateLabel(i);
			highest = (float)node->getBelief(i);
		}
	}
	return stateName;
}
void BayesianNetwork::EnterEvidence(std::string nodeName,std::string stateName)
{
	domain->uncompile();
	NodeList nodes = domain->getNodes();
	DiscreteChanceNode* evidenceNode;
	
	for (NodeList::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		Node* node = *it;
		if(nodeName == node->getName())
		{
			evidenceNode = dynamic_cast<DiscreteChanceNode*>(node);
			size_t index = evidenceNode->getStateIndex(stateName);
			evidenceNode->selectState(index);
			break;
		}
	}
	domain->compile();
	domain->propagate(H_EQUILIBRIUM_SUM, H_MODE_NORMAL);
}
void BayesianNetwork::RetractEvidence(std::string nodeName)
{
	domain->uncompile();
	DiscreteChanceNode* evidenceNode = dynamic_cast<DiscreteChanceNode*>(domain->getNodeByName(nodeName));
	evidenceNode->retractFindings();
	domain->compile();
	domain->propagate(H_EQUILIBRIUM_SUM, H_MODE_NORMAL);
}
void BayesianNetwork::PrintNodes()
{
	NodeList nodes = (domain)->getNodes();
	for (NodeList::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		DiscreteChanceNode* node = dynamic_cast<DiscreteChanceNode*>(*it);
		BWAPI::Broodwar->printf("Node: %s",node->getName().c_str());
		for(int i =0;i<(int)node->getNumberOfStates();i++)
		{
			BWAPI::Broodwar->printf("-State %s - probability %f",node->getStateLabel(i).c_str(),node->getBelief(i));
		}
	}
}


void BayesianNetwork::PrintMostProbableState(std::string nodeName)
{
	float highest = 0.0;
	std::string stateName = "";
	DiscreteChanceNode* node = dynamic_cast<DiscreteChanceNode*>(domain->getNodeByName(nodeName));
	for(int i =0;i<(int)node->getNumberOfStates();i++)
	{
		if((float)node->getBelief(i) > highest)
		{
			stateName = node->getStateLabel(i);
			highest = (float)node->getBelief(i);
		}
	}
	BWAPI::Broodwar->printf("Highest probability of %s is state %s with the probability %f",nodeName.c_str(),stateName.c_str(),highest);
}

void BayesianNetwork::PrintToFile(std::string nodeName)
{

	DiscreteChanceNode* node = dynamic_cast<DiscreteChanceNode*>(domain->getNodeByName(nodeName));
	std::ofstream gameData2;
	gameData2.open("C:/spawnPredictor.lgdat", std::ios::out | std::ios::app);
	for(int i =0;i<(int)node->getNumberOfStates();i++)
	{
		gameData2 << node->getBelief(i) <<"; ";
	
	}
	gameData2 << "0 \n";
	gameData2.close();
	
}