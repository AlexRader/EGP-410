#include "EscapeMessage.h"
#include "Game.h"
#include "GameApp.h"

EscapeMessage::EscapeMessage()
	:GameMessage(ESCAPE_MESSAGE)
{
}

EscapeMessage::~EscapeMessage()
{
}

void EscapeMessage::process()
{
	gpGame->markForExit();
}