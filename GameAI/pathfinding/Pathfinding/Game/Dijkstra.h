#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;


class Dijkstra : public GridPathfinder
{
public:
	Dijkstra(Graph* pGraph);
	~Dijkstra();

	const Path& findPath(Node* pFrom, Node* pTo); // delete when done
private:

};
