/*
 * ActorGraph.h
 * Author: <Jihoon You>
 * Date:   <March 13 2017>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map> 
#include <queue>
#include "ActorNode.h"
#include "ActorEdge.h"
#include <stack>
using namespace std;

/*class compare for prioirty queue*/
class comp
{
	public:
	bool operator()(ActorNode*& lhs, ActorNode*& rhs) 
	{
		return *lhs < *rhs;
	}

};

class ActorGraph {
protected:
  
    //Data structures for pathfinder.
		unordered_map<string, ActorNode*> firstmap;
		unordered_map<string, ActorEdge*> secondmap;

		//Data structures for ActorConnection.
		unordered_map<string, ActorNode*> emptyWithActors;
		priority_queue<pair<int, ActorEdge*>> edgepq;
		//temporary data structure for traverse
		stack<pair<int, ActorEdge*>> temp;

		//default min_year 
		int min_year = 9999;

public:
    ActorGraph(void);


		/**      
		 * write output that contatins two actors and year.
		 *
		 * in_filename - intput pairfile
		 * out_filename - write out to the output file.
		 * return true moveinfo is correctedly written to the out_filename
		 */
		bool spanning(const char* in_filename, string out_filename);

		/**      
		 * Breadth first search thorugh graph. use it for actorconnections
		 *
		 * actorname1 - string readed from the first movie pair.
		 * actorname2 - string readed from the second movie pair.
		 * return true if two actors are connected
		 */
		bool BFSTraversee(string actorName1, string actorName2);

		/**      
		 * This functions uses for weighted graph.
		 *
		 * actorName1 = string readed from the first movie pair.
		 * actorName2 = string readed from the second movie pair.      
		 * return  AcotNode* if two actors are connected.
		 */
		ActorNode* Dijkstra(string actorName1, string actorName2);

		/**      
		 * Breadth first search through graph. use it for pathfinder.
		 *
		 * actorName1 = string readed from the first movie pair.
		 * actorName2 = string readed from the second movie pair.      
		 *      
		 * return ActorNode* if two actors are connected.
		 */
		ActorNode* BFSTraverse(string actorName1, string actorName2);  
		/**      
		 * This resetHelper function resets some nodes in graph for BFS
	   */
		void resetHelper();

		/**      
		 *	This resetHelper2 function resets some nodes in graph for BFS
		 *
		 * return true if file was loaded sucessfully, false otherwise
		 */
		void resetHelper2();		

		/**      
		 * Unlike the previous loadFromFile this takes one parameter.
		 * This is function is created for the actorconnections. 
		 *
		 * in_filename - input filename
		 *      
		 * return true if file was loaded sucessfully, false otherwise
		 */
		bool loadFromFile(const char* in_filename);


		/** You can modify this method definition as you wish
		 *
		 * Load the graph from a tab-delimited file of actor->movie relationships.
		 *
		 * in_filename - input filename
		 * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
		 *
		 * return true if file was loaded sucessfully, false otherwise
		 */
		bool loadFromFile(const char* in_filename, bool use_weighted_edges);

		/*Destructor*/
		~ActorGraph();  
};


#endif // ACTORGRAPH_H
