#include "Game.h"
#include "GameMessageManager.h"
#include "PlusMinusMessage.h"


PlusMinusMessage::PlusMinusMessage(const float var)
	:GameMessage(PLUS_MINUS)
	, mVar(var)
{

}
PlusMinusMessage::~PlusMinusMessage()
{

}

void PlusMinusMessage::process()
{
	gpGame->getInputManager()->setSwitch(mVar);
}