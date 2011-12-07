// BayesianNetworkTest.cpp : main project file.
#include<iostream>
#include "BayesianNetwork.h"
#include "Node.h"
#include "ProbabilityHelper.h"
using namespace std;

int main()
{
	//cout<<ProbabilityHelper::aIntersectB(.2,.5)<<endl;


	double table1[2];
	double table2[2];

	table1[0]=.5;
	table1[1]=.5;
	table2[0]=.99999;
	table2[1]=.00001;
	cout << table1[0] <<"| "<<table1[1]<<endl;
	cout << table2[0] <<"| "<<table2[1]<<endl;

	double tableJoint[2][2];

	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			tableJoint[j][i]=table1[i]*table2[j];
		}
	}

	//AnB
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			cout<<tableJoint[i][j]<<"    ";
		}
		cout<<endl;
	}

	//A|B
	double AgivenB[2][2];


	//A|B
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			//Table2 = P(B). I think use I to get the right values
			AgivenB[i][j]=tableJoint[i][j]/table2[i];
			//watch for divide by zero!

		}
	}

	cout<<"\n\n\n";
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			cout<<AgivenB[i][j]<<"    ";
		}
		cout<<endl;
	}

    return 0;
}
