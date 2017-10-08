

#include "Game.h"
#include "GameMessageManager.h"
#include "AngularControl.h"


AngularControl::AngularControl(const float var)
	:GameMessage(A_CONTROL)
	, mVar(var)
{

}
AngularControl::~AngularControl()
{

}

void AngularControl::process()
{
	gpGame->getUnitManager()->setAngularVelocity(mVar);
}