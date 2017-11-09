#include "PathDisplayDijkstraMessage.h"
#include "Game.h"
#include "GameApp.h"

PathDisplayDijkstraMessage::PathDisplayDijkstraMessage(const std::string path)
	:GameMessage(DIJKSTRA_TRACK_MESSAGE)
	, mPathType(path)
{
}

PathDisplayDijkstraMessage::~PathDisplayDijkstraMessage()
{
}

void PathDisplayDijkstraMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	pGame->changePath(mPathType);
}