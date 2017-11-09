#include "PathDisplayAstarMessage.h"
#include "Game.h"
#include "GameApp.h"

PathDisplayAstarMessage::PathDisplayAstarMessage(const std::string path)
	:GameMessage(DIJKSTRA_TRACK_MESSAGE)
	,mPathType(path)
{
}

PathDisplayAstarMessage::~PathDisplayAstarMessage()
{
}

void PathDisplayAstarMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	pGame->changePath(mPathType);
}