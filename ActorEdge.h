/*
 * ActorEdge.h
 * Author: <Jihoon You>
 * Date:   <March 13 2017>
 */
#ifndef ACTOREDGE_H
#define ACTOREDGE_H
#include <vector>
#include <string>
using namespace std;

class ActorNode;
class ActorEdge{
	public:
		string title;
		int year;
		int weight;
		vector<ActorNode*> cast;


		//constructor
		ActorEdge(string title = NULL, int year = 0, int weight = 2015)
			: title(title), year(year), weight(weight){}


};

#endif // ACTOREDGE_H
