/*
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA4
 * */

#include "ActorNode.h"

using namespace std;


bool ActorNode::operator<(const ActorNode& other)
{
	//if dist is not equal
	if(dist != other.dist)
	{
		return dist > other.dist;	
	}

	//if dist is equal
	return specialN > other.specialN;
}

