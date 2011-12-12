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
			break;
		}
	}
	return 0.0;
}
void BayesianNetwork::EnterEvidence(std::string nodeName,std::string stateName)
{
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
}
void BayesianNetwork::PrintNodes()
{
	NodeList nodes = (domain)->getNodes();
    for (NodeList::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
		Node *node = *it;
		BWAPI::Broodwar->printf("name: %s",node->getName().c_str());
	}
}

