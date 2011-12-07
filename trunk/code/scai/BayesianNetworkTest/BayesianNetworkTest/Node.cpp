#include "Node.h"

Node::Node(int x,int y)
{
	statesX[x];
	statesY[y];
	table[x][y];
	
}

Node::~Node(void)
{
}

void Node::addChild(Node child)
{
	children.push_back(child);
}

void Node::addParent(Node parent)
{
	parents.push_back(parent);
}

void Node::addStateX(string state)
{
	statesX.push_back(state);
}
void Node::addStateY(string state)
{
	statesY.push_back(state);
}

std::string Node::mostProbable()
{


	return 0;
}

void Node::updateTable()
{
	if(!parents.empty())
	{

	}
}

vector<string> Node::getStatesX()
{
	return statesX;
}
vector<string> Node::getStatesY()
{
	return statesY;
}