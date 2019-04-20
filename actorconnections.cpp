/*
 * actorConnections.cpp
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
	if(argc != 5)
	{
		cout << "Incorrect number of arguments \n";
		return -1;
	}

	ActorGraph theGraph;
	const char* movieInfo;
	const char* pairFile;
	string outFile;
	string choice;
	bool flag;

	movieInfo = argv[1];
	pairFile = argv[2];
	outFile = argv[3];
	choice = argv[4];

	if(choice.compare("ufind"))
	{
		flag = true;	
	}
	else if(choice.compare("bfs"))
	{
		flag = false;
	}
	else
	{
		cout << "Wrong parameter" << endl;
		return -1;
	}

	//loading movieinfo
	theGraph.loadFromFile(movieInfo);


	theGraph.spanning(pairFile, outFile);

return -1;
}
