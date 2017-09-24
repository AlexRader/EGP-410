#pragma once


#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class SpawnDynamicSeek :public GameMessage
{
public:
	SpawnDynamicSeek(const Vector2D& pos);
	~SpawnDynamicSeek();

	void process();

private:
	Vector2D mPos;
};