#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;
struct NodeRecord;

using namespace std;

class Astar : public GridPathfinder
{
public:
	Astar(Graph* pGraph);
	~Astar();

	const Path& findPath(Node* pFrom, Node* pTo); // delete when done
	NodeRecord* getSmallest(vector<NodeRecord*> list); // returns the smallest node in open list
	NodeRecord* getListNode(vector<NodeRecord*> list, NodeRecord* checkedNode); // returns if the closed list contains the end node
	int getNodePosition(vector<NodeRecord*> list, NodeRecord* checkedNode); // returns the position of a node

private:
};