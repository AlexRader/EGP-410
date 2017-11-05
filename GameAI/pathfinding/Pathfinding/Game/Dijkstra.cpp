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
	// initialize the startnode and connections
	NodeRecord* startRecord = new NodeRecord();
	startRecord->mNode = pFrom;
	startRecord->mMyConnection = NULL;
	startRecord->mCost = 0;

	// initializing open and closed lists
	vector<NodeRecord*> open;
	open.push_back(startRecord);
	vector<NodeRecord*> closed;

	while (open.size() > 0)
	{
	}
}

