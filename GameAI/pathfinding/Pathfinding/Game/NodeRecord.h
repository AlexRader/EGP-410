#pragma once

#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

struct NodeRecord : public Trackable
{
	NodeRecord* mMyConnection;
	Node* mNode;
	float mCost;
};