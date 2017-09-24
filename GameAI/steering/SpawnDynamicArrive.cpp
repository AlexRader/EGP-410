#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "SpawnDynamicArrive.h"
#include "UnitManager.h"

SpawnDynamicArrive::SpawnDynamicArrive(const Vector2D& pos)
	:GameMessage(ARRIVE_SPAWN)
	, mPos(pos)
{
}

SpawnDynamicArrive::~SpawnDynamicArrive()
{
}

void SpawnDynamicArrive::process()
{
	//gpGame->getPlayerUnit()->arrive(mPos);

	gpGame->createUnit(DYNAMIC_ARRIVE, mPos);
}