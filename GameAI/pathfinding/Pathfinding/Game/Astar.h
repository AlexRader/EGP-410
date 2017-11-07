#pragma once

#include "GridPathfinder.h"
#include <vector>
#include "Vector2D.h"


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
	NodeRecord* getSmallest(vector<NodeRecord*> list, Node* destination); // returns the smallest node in open list
	NodeRecord* getListNode(vector<NodeRecord*> list, NodeRecord* checkedNode); // returns if the closed list contains the end node
	int getNodePosition(vector<NodeRecord*> list, NodeRecord* checkedNode); // returns the position of a node
	float getDistance(Vector2D first, Vector2D second); // distance to point

private:
	Grid* mpGrid;
};