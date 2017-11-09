#pragma once

#include "Pathfinder.h"
#include <allegro5/allegro.h>
class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual const Path& findPath( Node* pFrom, Node* pTo ) = 0;

	inline void setPathColor(float r, float g, float b) { mPathColor = al_map_rgb(r, g, b); };
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
protected:
	std::vector<Node*> mVisitedNodes;
	GridVisualizer* mpVisualizer;
	ALLEGRO_COLOR mPathColor; // adding this so I can modify the path color
#endif

	double mTimeElapsed;
};