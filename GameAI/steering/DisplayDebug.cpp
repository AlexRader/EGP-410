#include "Game.h"
#include "GameMessageManager.h"
#include "DisplayDebug.h"


DisplayDebug::DisplayDebug()
	:GameMessage(DISPLAY_DEBUG)
{

}
DisplayDebug::~DisplayDebug()
{

}

void DisplayDebug::process()
{
	gpGame->changeDebug();
}