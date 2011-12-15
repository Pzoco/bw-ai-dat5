#pragma once
#include <BWAPI.h>
#include "hugin"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace HAPI;

class BayesianNetwork
{
public:
	BayesianNetwork();
	BayesianNetwork(std::string fileName);
	void EnterEvidence(std::string nodeName,std::string stateName);
	void RetractEvidence(std::string nodeName);
	float GetProbability(std::string nodeName,std::string stateName);
	std::string GetMostProbableState(std::string nodeName);
	void PrintNodes();
	void PrintMostProbableState(std::string nodeName);
	void PrintToFile(std::string nodeName);
private:
	Domain* domain;
};
