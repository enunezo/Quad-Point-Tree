#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class node{
public:
	tuple<int, int> point;
	int pageSize = 4;
	node * sons[4];
	/*
	sons[0] -> northWest
	sons[1] -> northEast
	sons[2] -> southEast
	sons[3] -> southWest

	0 | 1
	-----
	3 | 2

	*/
	node(){
		for (int i = 0; i < pageSize; ++i){
			sons[i]=NULL;
		}
	}

	node( int x, int y){
		get<0>(point)=x;
		get<1>(point)=y;
		for (int i = 0; i < pageSize; ++i){
			sons[i]=NULL;
		}
	}

	node & operator = (node a){
		get<0>(point) = get<0>(a.point);
		get<1>(point) = get<1>(a.point);
		return *this;
	}

	void print(){
		cout<<get<0>(this->point)<<","<<get<1>(this->point);
	}
	~node(){}
};