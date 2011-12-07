#pragma once
#include <list>
#include "Node.h"
class BayesianNetwork
{
public:
	BayesianNetwork(void);
	~BayesianNetwork(void);
	void addNode(Node n);
private:
	std::list<Node> nodes;
};
