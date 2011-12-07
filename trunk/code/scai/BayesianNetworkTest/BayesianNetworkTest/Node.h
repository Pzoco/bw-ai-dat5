#pragma once
#include<list>
#include<vector>
#include<iostream>
using namespace std;
class Node
{
public:
	Node(int x,int y);
	~Node(void);
	void addChild(Node child);
	void addParent(Node parent);
    string mostProbable();

	void addStateX(string state);
	void addStateY(string state);
	void updateTable();

	vector<string> getStatesX();
	vector<string> getStatesY();
private:
	list<Node> children;
	list<Node> parents;
	
	//markov blanket
	list<Node> childrenParents;
	//state titles
	vector<string> statesX;
	vector<string> statesY;


	//the table of probablities
	vector<vector<double>> table;


};
