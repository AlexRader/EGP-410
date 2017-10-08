#include "Game.h"
#include "GameMessageManager.h"
#include "RadiusChange.h"


RadiusChange::RadiusChange(const float var)
	:GameMessage(R_CONTROL)
	,mVar(var)
{

}
RadiusChange::~RadiusChange()
{

}

void RadiusChange::process()
{
	gpGame->getUnitManager()->setRadius(mVar);
}