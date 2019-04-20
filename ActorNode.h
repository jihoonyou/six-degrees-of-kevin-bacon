/*
 * ActorNode.h
 * Author: <Jihoon You>
 * Date:   <March 13 2017>
 */
#ifndef ACTORNODE_H
#define ACTORNODE_H
#include <vector>
#include <limits>
#include <string>
#include "ActorEdge.h"

using namespace std;

class ActorNode{
	public:

		string name;
		vector<ActorEdge*> edges;
		bool visit;
		int dist;
		ActorNode* prev;
		string connection;
		int specialN;
		bool noexist;
		//constructor
		ActorNode(string name, bool visit = false, int dist = numeric_limits<int>::max(), ActorNode* prev = nullptr, string connection = "", bool noexist = false)
			: name(name), visit(visit), dist(dist), prev(prev) {}

		//compare for prioirty queue
		bool operator<(const ActorNode& other);

};

#endif 
