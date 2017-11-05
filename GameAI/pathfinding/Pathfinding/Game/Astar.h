#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;


class Astar : public GridPathfinder
{
public:
	Astar(Graph* pGraph);
	~Astar();

	//const Path& findPath(Node* pFrom, Node* pTo); // delete when done
private:

};