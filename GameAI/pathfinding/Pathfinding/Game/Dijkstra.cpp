#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include "NodeRecord.h"


using namespace std;

Dijkstra::Dijkstra(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

Dijkstra::~Dijkstra()
{
}


const Path& Dijkstra::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	mPath.clear();

	//list to be deleted
	vector<NodeRecord*> mpListToDelete;

	// initialize the startnode and connections
	NodeRecord* startRecord = new NodeRecord();
	startRecord->mNode = pFrom;
	startRecord->mMyConnection = NULL;
	startRecord->mCost = 0;

	mpListToDelete.push_back(startRecord);

	// initializing open and closed lists
	vector<NodeRecord*> open;
	open.push_back(startRecord);
	vector<NodeRecord*> closed;

	//initialize a temp variable to store current node
	NodeRecord* current;
	//position of deleted node
	int position;
	while (open.size() > 0)
	{
		//initialize a temp variable to store current node
		//NodeRecord* current;
		NodeRecord* nodeToAdd;
		//initializes the connections
		vector<Connection*> connections;
		//initializes the end node and end node cost
		NodeRecord* endNode;
		float endNodeCost = 0.0f;
		current = getSmallest(open); // get the next node to be checked
		// checks if the current node is the destination else get its connections
		if (current->mNode == pTo)
			break;
		else
			connections = mpGraph->getConnections(current->mNode->getId());
		// updating connections in open list or adding to open list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			endNode = new NodeRecord();
			endNode->mNode = pConnection->getToNode();

			mpListToDelete.push_back(endNode);

			endNodeCost = current->mCost + pConnection->getCost();
			//check if node is already closed
			if (getListNode(closed, endNode) != NULL)
				continue;
			else if (getListNode(open, endNode) != NULL) // if in open check if it is a better path
			{
				nodeToAdd = getListNode(open, endNode);
				if (nodeToAdd->mCost <= endNodeCost)
					continue;
			}
			else // found a new node
			{
				//nodeToAdd = endNode;
				nodeToAdd = endNode;
				nodeToAdd->mNode = endNode->mNode;
			}
			//updating cost and connections
			nodeToAdd->mCost = endNodeCost;
			nodeToAdd->mMyConnection = current;
			
			//if open does not contain node
			if (!getListNode(open, endNode))
				open.push_back(nodeToAdd);
		}
		position = getNodePosition(open, current); // find node position
		open.erase(open.begin() + position);
		closed.push_back(current);
	}
	if (current->mNode != pTo)
	{}
	else // get the path
	{
		while (current->mNode != pFrom)
		{
			mPath.addNode(current->mNode);
#ifdef VISUALIZE_PATH
			mVisitedNodes.push_back(current->mNode); // visualizes the path
#endif
			current = current->mMyConnection;
		}
	}
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	//cleanup the memory leaks
	for (unsigned int i = 0; i < mpListToDelete.size(); i++)
	{
		delete mpListToDelete.at(i);
		mpListToDelete.at(i) = NULL;
	}

	return mPath;
}

// returns smallest element
NodeRecord* Dijkstra::getSmallest(vector<NodeRecord*> list)
{
	//initializes temp and return value
	NodeRecord* temp;
	NodeRecord* returnNode;

	returnNode = list.at(0); // start with a default value
	for (unsigned int i = 0; i < list.size(); ++i)
	{
		temp = list.at(i);
		// switches the return value to smallest element
		if (temp->mCost < returnNode->mCost)
			returnNode = temp;
	}

	return returnNode;
}

//returns the position of a node
int Dijkstra::getNodePosition(vector<NodeRecord*> list, NodeRecord* checkedNode)
{
	// check if the node exists in the list
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list.at(i) == checkedNode)
			return i; // return the existing node position
	}
	return -1;
}

//returns if the node is in the given list
NodeRecord* Dijkstra::getListNode(vector<NodeRecord*> list, NodeRecord* checkedNode)
{
	// check if the node exists in the list
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->mNode == checkedNode->mNode)
			return checkedNode; // return the existing node
	}
	return NULL;
}

