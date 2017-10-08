#include "Game.h"
#include "GameMessageManager.h"
#include "EscapeMessage.h"


EscapeMessage::EscapeMessage()
	:GameMessage(ESCAPE_MESSAGE)
{

}
EscapeMessage::~EscapeMessage()
{

}

void EscapeMessage::process()
{
	gpGame->changeEscape();
}