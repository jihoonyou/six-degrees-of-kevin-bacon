/*
 * ActorGraph.cpp
 * Author: <Jihoon You>
 * Date:   <March 13 2017>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include "ActorGraph.h"
#include "ActorNode.h"

using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::spanning(const char* in_filename, string out_filename)
{

	priority_queue<pair<int, ActorEdge*>, vector<pair<int,ActorEdge*>>> temppq;
	// Initialize the file stream
	ifstream infile(in_filename);
	ofstream out(out_filename);

	bool have_header = false;

	//writing header
	out << "Actor1\tActor2\tYear" << endl;

	// keep reading lines until the end of file is reached
	while (infile) 
	{
		string s;
		// get the next line
		if (!getline( infile, s )) break;

		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

			// get the next string before hitting a tab character and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 2) {
			// we should have exactly 2 columns
			continue;
		}

		// get the next line
		string actor_name1 = record[0];
		string actor_name2 = record[1];
		temppq = edgepq;
		while(!temppq.empty())
		{
			temp.push(temppq.top());
			min_year = temppq.top().second->year;
			temppq.pop();
			for(auto it = temp.top().second->cast.begin(); it!= temp.top().second->cast.end(); ++it)
			{
				emptyWithActors[(*it)->name]->edges.push_back(temp.top().second);	
			}
			bool check = BFSTraversee(actor_name1, actor_name2);
			if(check == true)
			{
				out << actor_name1 << "\t" << actor_name2 << "\t" << min_year <<endl;
				min_year = 9999;
				temp.pop();
				continue;
			}
			temp.pop();

		}
	/*	if (!infile.eof()) {
			cerr << "Failed to read " << in_filename << "!\n";
			return false;
		}*/
	
		continue;
	}
	return true;
}

bool ActorGraph::BFSTraversee(string actorName1, string actorName2)
{
	resetHelper2();
	queue<ActorNode*> toExplore;

	ActorNode* start = emptyWithActors[actorName1];
	ActorNode* end = emptyWithActors[actorName2];

	ActorNode* neighbor;
	start->dist = 0;
	toExplore.push(start);
	start->visit = true;

	while (!toExplore.empty())
	{
		ActorNode* curr = toExplore.front();
		toExplore.pop();
		auto it = curr->edges.begin();
		for(; it != curr->edges.end(); ++it)
		{
			auto it2 = (*it)->cast.begin();
			for(;it2 != (*it)->cast.end(); ++it2)
			{
				neighbor = (*it2);
				if(!neighbor->visit && curr->dist +1 < neighbor->dist)
				{
					neighbor->dist = curr->dist + 1;
					neighbor->prev = curr;
					neighbor->connection = (*it)->title + "#@" + to_string((*it)->year);
					if(!neighbor->visit)
					{
						toExplore.push(neighbor);
						neighbor->visit = true;
					}
					if(end == neighbor)
					{
					cout <<"never here huh"<< endl;
						return true;	
					}
				}
			}	
		}
	}
	//when two nodes are not connected
	if(end != neighbor)
	{
		return false;
	}
}

ActorNode* ActorGraph::Dijkstra(string actorName1, string actorName2)
{

	resetHelper();


	//check if actorName is in the node
	auto got = firstmap.find(actorName1);
	if(got == firstmap.end())
	{
		ActorNode* noActor = new ActorNode(actorName1, 0);
		noActor->noexist = true;
		return noActor;
	}

	//check if actorName is in the node
	auto got2 = firstmap.find(actorName2);
	if(got2 == firstmap.end())
	{
		ActorNode* noActor = new ActorNode(actorName2, 0);
		noActor->noexist = true;
		return noActor;
	}

	priority_queue<ActorNode*, vector<ActorNode*>,comp> pq;


	ActorNode* start = firstmap[actorName1];
	ActorNode* end = firstmap[actorName2];
	ActorNode* neighbor;
	start->dist = 0;

	pq.push(start);
	while(!pq.empty())
	{

		ActorNode* curr = pq.top();
		pq.pop();
		if(!curr->visit)
		{
			curr->visit = true;
		}
		if(curr->visit && end == curr)
		{
			return curr;
		}

		auto it = curr->edges.begin();
		for(; it != curr->edges.end(); ++it)
		{
			//store weight for the edge
			int cost = curr->dist + (*it)->weight;
			auto it2 = (*it)->cast.begin();
			for(;it2 != (*it)->cast.end(); ++it2)
			{
				neighbor = (*it2);

				if(!neighbor->visit && cost < neighbor->dist)
				{
					neighbor->dist = cost;
					neighbor->prev = curr;
					neighbor->connection = (*it)->title + "#@" + to_string((*it)->year);
					pq.push(neighbor);

				}
			}	
		}
	}
}


ActorNode* ActorGraph::BFSTraverse(string actorName1, string actorName2)
{
	resetHelper();

	queue<ActorNode*> toExplore;
	
	//check if actorName is in the node
	auto got = firstmap.find(actorName1);
	if(got == firstmap.end())
	{
		ActorNode* noActor = new ActorNode(actorName1, 0);
		return noActor;
	}
	//check if actorName is in the node
	auto got2 = firstmap.find(actorName2);
	if(got2 == firstmap.end())
	{
		ActorNode* noActor = new ActorNode(actorName2, 0);
		return noActor;
	}

	ActorNode* start = firstmap[actorName1];
	ActorNode* end = firstmap[actorName2];
	ActorNode* neighbor;
	start->dist = 0;
	toExplore.push(start);
	start->visit = true;

	while (!toExplore.empty())
	{
		ActorNode* curr = toExplore.front();
		toExplore.pop();
		//iterate through Actornode->edges
		auto it = curr->edges.begin();
		for(; it != curr->edges.end(); ++it)
		{
			//iterate through ActorEdge->cast
			auto it2 = (*it)->cast.begin();
			for(;it2 != (*it)->cast.end(); ++it2)
			{
				neighbor = (*it2);
				if(!neighbor->visit && curr->dist +1 < neighbor->dist)
				{
					neighbor->dist = curr->dist + 1;
					neighbor->prev = curr;
					neighbor->connection = (*it)->title + "#@" + to_string((*it)->year);
					if(!neighbor->visit)
					{
						toExplore.push(neighbor);
						neighbor->visit = true;
					}
					//when two nodes are connected
					if(end == neighbor)
					{
						return neighbor;	
					}
				}
			}	
		}
	}

	//when two nodes are not connected
	if(end != neighbor)
	{
		return NULL;
	}
}

/*helper function*/
void ActorGraph::resetHelper(){
	auto it = firstmap.begin();
	for(; it!= firstmap.end(); ++it)
	{
		it->second->dist = numeric_limits<int>::max();
		it->second->visit = false;
		it->second->prev = nullptr;
		it->second->connection = "";
	}
}
/*helper function*/	
void ActorGraph::resetHelper2(){	
	auto it = emptyWithActors.begin();
	for(; it!= emptyWithActors.end(); ++it)
	{
		it->second->dist = numeric_limits<int>::max();
		it->second->visit = false;
		it->second->prev = nullptr;
		it->second->connection = "";
	}
}

bool ActorGraph::loadFromFile(const char* in_filename) {
	// Initialize the file stream
	ifstream infile(in_filename);

	int specialNumber = 0;
	bool have_header = false;

	// keep reading lines until the end of file is reached
	while (infile) {
		string s;

		// get the next line
		if (!getline( infile, s )) break;

		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

			// get the next string before hitting a tab character and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 3) {
			// we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);
		string secondKey = movie_title + to_string(movie_year);
			//if a key does not exist, create the key.
			if(firstmap.find(actor_name) == firstmap.end())
			{
				ActorNode* actor = new ActorNode(actor_name);
				actor->specialN = specialNumber++;
				firstmap[actor_name] = actor;

				//this is for ActorConnections
				ActorNode* otherActor = new ActorNode(actor_name);
				emptyWithActors[actor_name] = otherActor;
			}
			//if a key does not exist, create the key.
			if(secondmap.find(secondKey)== secondmap.end())
			{
				int weight = 1 + (2015 - movie_year);
				ActorEdge* edge = new ActorEdge(movie_title, movie_year, weight);
				edge->cast.push_back(firstmap[actor_name]);
				secondmap[secondKey] = edge;
				//adding movie to a node;
				firstmap[actor_name]->edges.push_back(edge);
				//sorting edge data structure
				edgepq.push(make_pair(edge->weight,edge));
			}
			else if(secondmap.find(secondKey) != secondmap.end())
			{
				secondmap[secondKey]->cast.push_back(firstmap[actor_name]);
				firstmap[actor_name]->edges.push_back((secondmap[secondKey]));
			}
	}

	if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
	// Initialize the file stream
	ifstream infile(in_filename);

	int specialNumber = 0;
	bool have_header = false;

	// keep reading lines until the end of file is reached
	while (infile) {
		string s;

		// get the next line
		if (!getline( infile, s )) break;

		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

			// get the next string before hitting a tab character and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 3) {
			// we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);
		string secondKey = movie_title + to_string(movie_year);
		// we have an actor/movie relationship, now what?

		if(use_weighted_edges == false) //unweighted graph
		{
			//if a key does not exist, create the key.
			if(firstmap.find(actor_name) == firstmap.end())
			{
				ActorNode* actor = new ActorNode(actor_name);
				actor->specialN = specialNumber++;
				firstmap[actor_name] = actor;
				}
				//if a key does not exist, create the key.
				if(secondmap.find(secondKey)== secondmap.end())
				{
					ActorEdge* edge = new ActorEdge(movie_title, movie_year);

					edge->cast.push_back(firstmap[actor_name]);
					secondmap[secondKey] = edge;
					//adding movie to a node;
					firstmap[actor_name]->edges.push_back(edge);
				}
				else if(secondmap.find(secondKey) != secondmap.end())
				{
					secondmap[secondKey]->cast.push_back(firstmap[actor_name]);
					firstmap[actor_name]->edges.push_back((secondmap[secondKey]));
				}
		}
		else //weighted graph
		{
			//if a key does not exist, create the key.
			if(firstmap.find(actor_name) == firstmap.end())
			{
				ActorNode* actor = new ActorNode(actor_name);
				actor->specialN = specialNumber++;
				firstmap[actor_name] = actor;

				//this is for ActorConnections
				ActorNode* otherActor = new ActorNode(actor_name);
				emptyWithActors[actor_name] = otherActor;
			}
			//if a key does not exist, create the key.
			if(secondmap.find(secondKey)== secondmap.end())
			{
				int weight = 1 + (2015 - movie_year);
				ActorEdge* edge = new ActorEdge(movie_title, movie_year, weight);
				edge->cast.push_back(firstmap[actor_name]);
				secondmap[secondKey] = edge;
				//adding movie to a node;
				firstmap[actor_name]->edges.push_back(edge);
			}
			else if(secondmap.find(secondKey) != secondmap.end())
			{
				secondmap[secondKey]->cast.push_back(firstmap[actor_name]);
				firstmap[actor_name]->edges.push_back((secondmap[secondKey]));
			}
		}
	}

	if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}
/*Destructor*/
ActorGraph::~ActorGraph(){

	auto it = firstmap.begin();
	for(; it!= firstmap.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = secondmap.begin();
	for(; it2!= secondmap.end(); ++it2)
	{
		delete it2->second;
	}
	auto it3 = emptyWithActors.begin();
	for(; it3 != emptyWithActors.end(); ++it3)
	{
		delete it3->second;
	}
}
