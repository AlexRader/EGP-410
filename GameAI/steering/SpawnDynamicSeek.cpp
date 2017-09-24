#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "SpawnDynamicSeek.h"
#include "UnitManager.h"

SpawnDynamicSeek::SpawnDynamicSeek(const Vector2D& pos)
	:GameMessage(SEEK_SPAWN)
	, mPos(pos)
{
}

SpawnDynamicSeek ::~SpawnDynamicSeek()
{
}

void SpawnDynamicSeek::process()
{
	//gpGame->getPlayerUnit()->arrive(mPos);

	gpGame->createUnit(DYNAMIC_SEEK, mPos);
}