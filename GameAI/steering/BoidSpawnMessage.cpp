#include "Game.h"
#include "GameMessageManager.h"
#include "BoidSpawnMessage.h"


BoidSpawnMessage::BoidSpawnMessage(const Vector2D& pos)
	:GameMessage(BOIDS_SPAWN)
	, mPos(pos)
{
	mBoidsToSpawn = 5.0f;
}

BoidSpawnMessage::~BoidSpawnMessage()
{
}
// spawns 5 boids at random locations
void BoidSpawnMessage::process()
{
	for (int i = 0; i < mBoidsToSpawn; i++)
	{
		mPos = gpGame->getSpawnPoint();
		mPos.setX(mPos.getX() + genRandomInteger());
		mPos.setY(mPos.getY() + genRandomInteger());


		gpGame->createUnit(DYNAMIC_ARRIVE, mPos);
	}
}