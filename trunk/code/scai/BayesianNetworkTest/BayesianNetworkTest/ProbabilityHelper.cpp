#include "ProbabilityHelper.h"



double ProbabilityHelper::notDisjointAUnionB(double A,double B)
{
	return A + B - aIntersectB(A,B);
}

double ProbabilityHelper::disjointAUnionB(double A,double B)
{
	return A+B;
}
double ProbabilityHelper::aIntersectB(double A, double B)
{
	return A*B;
}

/*
void ProbabilityHelper::notDisjointAUnionB(vector<double> A, vector<double> B])
{

}

void ProbabilityHelper::disjointAUnionB(vector<double> A, vector<double> B])
{
	
}
void ProbabilityHelper::aIntersectB(vector<double> A, vector<double> B])
{
	
}
*/