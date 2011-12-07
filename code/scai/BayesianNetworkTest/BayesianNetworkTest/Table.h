#pragma once
#include <vector>
#include <string>
using namespace std;
class Table
{
public:
	Table(int x, int y);
	~Table(void);
	void addStateX(string state, int pos);
	void addStateY(string state, int pos);
	void setValue(double val, int x,int y);
	double getValue(int x,int y);
private:
	vector<vector<double>> table;
	vector<string> xStates;
	vector<string> yStates;
};
