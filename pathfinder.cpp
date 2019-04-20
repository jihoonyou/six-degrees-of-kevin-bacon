/*
 * pathfinder.cpp
 * Author: <Jihoon You>
 * Date:   <March 13 2017>
 */
#include "ActorEdge.h"
#include "ActorGraph.h"
#include "ActorNode.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <stack>
#include <cstring>
using namespace std;


int main(int argc, const char *argv[])
{

	/*check arguments*/
	if(argc != 5)
	{
		cout << "Incorrect number of arguments.\n";
		return -1;
	}

	ActorGraph theGraph;
	const char* m;
	const char* c;
	const char* pairFile;
	string o;


	bool flag;
	stack<ActorNode*> paths;
	ActorNode* check;
	
	m = argv[1];
	c = argv[2];
	pairFile = argv[3];
	o = argv[4];

	/*check parameter for u or w */
	if(strcmp(c, "u") == 0)
	{
		flag = false;

	}
	else if(strcmp(c, "w") == 0)
	{
		flag = true;
	}
	else
	{
		cout << "Wrong parameter '"<< c << "'" <<" must be u or w \n";
		return -1;
	}

	//loading movieinfo and create a graph
	theGraph.loadFromFile(m, flag);

	//loading PairFile
	// Initialize the file stream
	ifstream infile(pairFile);

	bool have_header = false;

	//write
	ofstream out;
	out.open(o);
	//writing header
	out << "(actor)--[movie#@year]-->(actor)--..." << endl;


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

		if (record.size() != 2) {
			// we should have exactly 2 columns
			continue;
		}

		string actor_name1 = record[0];
		string actor_name2 = record[1];


		//now call BFTraverse or Dijskstra
		if(!flag)
		{
		check = theGraph.BFSTraverse(actor_name1,actor_name2);
		}
		else
		{
		check = theGraph.Dijkstra(actor_name1,actor_name2);
		}		


		if(check == NULL)
		{
			out << "\n";
			continue;
		}
		else if((!flag && check->visit == false) )
		{
			cout<< "Failed to locate node "<< "'" << check->name <<"'" << endl;
			cout<< "./pathfinder called with incorrect arguments." << endl;
			return -1;
		}
		else if(flag && check->noexist ==true)
		{

			cout<< "Failed to locate node "<< "'" << check->name <<"'" << endl;
			cout<< "./pathfinder called with incorrect arguments." << endl;
			return -1;


		}
		paths.push(check);
		//write to outfile
		while(paths.top()->prev)
		{
			paths.push(paths.top()->prev);
		}
		while(!paths.empty())
		{
			if(paths.top()->connection != "")
			{
				out << "[" << paths.top()->connection << "]"<< "-->";
			}
			if(paths.size() == 1)
			{
				out << "("<< paths.top()->name << ")";
			}
			else
			{
				out << "("<< paths.top()->name << ")"<< "--";
			}

			if(paths.size() == 1)
			{
				out << "\n";
			}	
			paths.pop();
	}
		continue;
	}

	/*if pairFile is incoorect*/
	if (!infile.eof()) {
		cerr << "Failed to read " << pairFile << "!\n";
		return -1;
	}
	infile.close();

	return -1;
}
