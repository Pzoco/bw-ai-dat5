#include "BayesianNetwork.h"

BayesianNetwork::BayesianNetwork(void)
{
}

BayesianNetwork::~BayesianNetwork(void)
{
}

void BayesianNetwork::addNode(Node n)
{
	nodes.push_back(n);
}
