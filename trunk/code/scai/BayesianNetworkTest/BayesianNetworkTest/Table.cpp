#include "Table.h"

Table::Table(int x,int y)
{
	table;
	table.resize(y,vector<double>(x,0.0));
}

Table::~Table(void)
{
}

void Table::addStateX(string state,int pos)
{
	xStates[pos]=state;
}

void Table::addStateY(string state,int pos)
{
	yStates[pos]=state;
}
void setValue(double val,int x,int y)
{
	//table[x][y] = val;
}

double getValue(int x,int y)
{
	return 1.1;// table[x][y];
}