#include <iostream>
#include "quadTree.h"

using namespace std;

int main(){

	quadTree a;
	a.insert(10000,-10000);
	a.insert(-10000,-10000);
	a.insert(100,100);
	a.insert(0,0);
	a.insert(15,15);		
	a.insert(10,10);
	a.print();
	node limitNW (-10001,11);
	node limitNE (11,-10001);
	node limitSW (-10001,11);
	node limitSE (11,-10001);
	vector<node *> limits;
	limits.push_back(&limitNW);
	limits.push_back(&limitNE);
	limits.push_back(&limitSE);
	limits.push_back(&limitSW);
	a.rangeQuery(limits);
	return 0;
}
