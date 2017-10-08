

#include "Game.h"
#include "GameMessageManager.h"
#include "EnemyVelocityControl.h"


EnemyVelocityControl::EnemyVelocityControl(const float var)
	:GameMessage(V_CONTROL)
	,mVar(var)
{

}
EnemyVelocityControl::~EnemyVelocityControl()
{

}

void EnemyVelocityControl::process()
{
	gpGame->getUnitManager()->setEnemyVelocity(mVar);
}