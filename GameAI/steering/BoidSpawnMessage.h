#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class BoidSpawnMessage :public GameMessage
{
public:
	BoidSpawnMessage(const Vector2D& pos);
	~BoidSpawnMessage();

	void process();

private:
	Vector2D mPos;
	int mBoidsToSpawn;
};