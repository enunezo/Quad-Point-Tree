#include <iostream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "node.h"

using namespace std;

class quadTree{
public:
	node * head;
	quadTree(){
		head = NULL;
	}

	bool isNorthWestPoint(int x, int y, node * current){
		return (x <= get<0>(current->point) && y >= get<1>(current->point));
	}

	bool isNorthEastPoint(int x, int y, node * current){
		return (x >= get<0>(current->point) && y >= get<1>(current->point));
	}

	bool isSouthEastPoint(int x, int y, node * current){
		return (x <= get<0>(current->point) && y <= get<1>(current->point));
	}

	bool isSouthWestPoint(int x, int y, node * current){
		return (x <= get<0>(current->point) && y <= get<1>(current->point));
	}

	
	/*bool insert(int x, int y){
		if ( !head ){
			node newNode(x,y) ;
			head = &newNode;
			newNode.print();
			cout<<endl;
			return true;
		}
		return insert(&head, x, y);
	}

	bool insert(node ** current, int x, int y){
		if (get<0>((*current)->point) == x && get<1>((*current)->point) == y){
			return false;
		}
		else{
			if ( isNorthWestPoint(x,y, *current) ){
				if( ! (*current)->sons[0] ){
					(*current)->sons[0] = new node(x,y);
					(*current)->sons[0]->print();
					cout<<"  "<<0<<endl;
					return true;
				}
				else {
					return insert((*current)->sons[0],x,y);
				}
			}
			else if ( isNorthEastPoint(x,y, *current) ){
				if( !(*current)->sons[1] ){
					(*current)->sons[1] = new node(x,y);;
					(*current)->sons[1]->print();
					cout<<"  "<<1<<endl;
					return true;
				}
				else {
					return insert((*current)->sons[1],x,y);
				}
			}
			else if ( isSouthEastPoint (x,y, *current) ){
				if( !(*current)->sons[2] ){
					(*current)->sons[2] = new node(x,y);
					(*current)->sons[2]->print();
					cout<<"  "<<2<<endl;
					return true;
				}
				else {
					return insert( (*current)->sons[2],x,y);
				}
			}
			else if ( isSouthWestPoint (x,y, *current) ){
				if( !(*current)->sons[3] ){
					(*current)->sons[3] = new node(x,y);
					(*current)->sons[3]->print();
					cout<<"  "<<3<<endl;
					return true;
				}
				else {
					return insert((*current)->sons[3],x,y);
				}
			}
			return false;
		}
		return false;
	}*/

	bool insert(int x, int y) {
        return insert(x, y, &head);
    }

    bool insert(int x, int y, node ** current) {
        if ( !(*current) ) {
            (*current) = new node (x, y);
            return true;
        }
        if (get<0>( (*current)->point ) == x && get<1>( (*current)->point) == y){
			return false;
		}
		else {
            if ( isNorthWestPoint(x,y, *current) ){
				return insert(x,y, &(*current)->sons[0]);
			}
			else if ( isNorthEastPoint(x,y, *current) ){
				return insert(x,y, &(*current)->sons[1]);
			}
			else if ( isSouthEastPoint (x,y, *current) ){
				return insert(x,y, &(*current)->sons[2]);
			}
			else {
				return insert(x,y, &(*current)->sons[3]);
			}
        }
        return false;
    }

    void print () {
		print(&head, 0);
	}

    void print (node ** current, int indent) {
		if (*current) {
			print(&(*current)->sons[0], indent+1);
			print(&(*current)->sons[1], indent+1);
			for (int i=0; i<indent; i++) cout << "    ";
			(*current)->print();
			cout<<endl;
			print(&(*current)->sons[2], indent+1);
			print(&(*current)->sons[3], indent+1);
		}
	}

	void rangeQuery(vector <node * >limits){
		return rangeQuery(limits, &head);
	}

	void rangeQuery( vector <node * >limits, node ** current){
		/*limits.at(0) = North West Limit;
		limits.at(1) = North East Limit;
		limits.at(2) = South East Limit;
		limits.at(3) = South West Limit;*/
		if ( !(*current) ) return;

		if (isSouthEastPoint(get<0>( (*current)->point ),get<1>( (*current)->point ), limits.at(0)) &&
			isSouthWestPoint(get<0>( (*current)->point ),get<1>( (*current)->point ), limits.at(1)) &&
			isNorthEastPoint(get<0>( (*current)->point ),get<1>( (*current)->point ), limits.at(2)) &&
			isNorthWestPoint(get<0>( (*current)->point ),get<1>( (*current)->point ), limits.at(3)) ){
				(*current)->print();
				cout<<endl;
				rangeQuery( limits, &(*current)->sons[0] );
				rangeQuery( limits, &(*current)->sons[1] );
				rangeQuery( limits, &(*current)->sons[2] );
				rangeQuery( limits, &(*current)->sons[3] );
				return;
		}
		else{

			if ( (*current)->sons[0]  &&
				isSouthEastPoint(get<0>( ((*current)->sons[0])->point ),get<0>( ((*current)->sons[0])->point ), limits.at(0)) &&
				isSouthWestPoint(get<0>( ((*current)->sons[0])->point ),get<0>( ((*current)->sons[0])->point ), limits.at(1)) &&
				isNorthEastPoint(get<0>( ((*current)->sons[0])->point ),get<0>( ((*current)->sons[0])->point ), limits.at(2)) &&
				isNorthWestPoint(get<0>( ((*current)->sons[0])->point ),get<0>( ((*current)->sons[0])->point ), limits.at(3))  ){
					((*current)->sons[0])->print();
					rangeQuery( limits, &(*current)->sons[0] );
					return;
			}
			else if((*current)->sons[1]  &&
					isSouthEastPoint(get<0>( ((*current)->sons[1])->point ),get<0>( ((*current)->sons[1])->point ), limits.at(0)) &&
					isSouthWestPoint(get<0>( ((*current)->sons[1])->point ),get<0>( ((*current)->sons[1])->point ), limits.at(1)) &&
					isNorthEastPoint(get<0>( ((*current)->sons[1])->point ),get<0>( ((*current)->sons[1])->point ), limits.at(2)) &&
					isNorthWestPoint(get<0>( ((*current)->sons[1])->point ),get<0>( ((*current)->sons[1])->point ), limits.at(3))  ){
					((*current)->sons[1])->print();
					rangeQuery( limits, &(*current)->sons[1] );
					return;
			}
			else if((*current)->sons[2]  &&
					isSouthEastPoint(get<0>( ((*current)->sons[2])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(0)) &&
					isSouthWestPoint(get<0>( ((*current)->sons[2])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(1)) &&
					isNorthEastPoint(get<0>( ((*current)->sons[2])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(2)) &&
					isNorthWestPoint(get<0>( ((*current)->sons[2])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(3))  ){
					((*current)->sons[2])->print();
					rangeQuery( limits, &(*current)->sons[2] );
					return;
			}
			else if((*current)->sons[3]  &&
					isSouthEastPoint(get<0>( ((*current)->sons[3])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(0)) &&
					isSouthWestPoint(get<0>( ((*current)->sons[3])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(1)) &&
					isNorthEastPoint(get<0>( ((*current)->sons[3])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(2)) &&
					isNorthWestPoint(get<0>( ((*current)->sons[3])->point ),get<0>( ((*current)->sons[2])->point ), limits.at(3))  ){
					((*current)->sons[3])->print();
					rangeQuery( limits, &(*current)->sons[3] );
					return;
			}
			else {
				return;
			}
		}

	}


	~quadTree(){}

	/* data */
};