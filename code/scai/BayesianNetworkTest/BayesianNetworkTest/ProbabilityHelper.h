#pragma once
#include <vector>
class ProbabilityHelper
{
public:
	static double notDisjointAUnionB(double A, double B);
	static double disjointAUnionB(double A, double B);
	static double aIntersectB(double A, double B);

	//static void notDisjointAUnionB(vector<double> A, vector<double> B);
	//static void disjointAUnionB(vector<double> A, vector<double> B);
	//static void aIntersectB(vector<double> A, vector<double> B);

};
