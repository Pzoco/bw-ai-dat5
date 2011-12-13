#pragma once
#include <BWAPI.h>
#include "hugin"
#include <iostream>
#include <string>
#include <algorithm>

using namespace HAPI;

class BayesianNetwork
{
public:
	BayesianNetwork();
	BayesianNetwork(std::string fileName);
	void EnterEvidence(std::string nodeName,std::string stateName);
	float GetProbability(std::string nodeName,std::string stateName);
	void PrintNodes();
	void PrintMostProbableState(std::string nodeName);
private:
	Domain* domain;
};
