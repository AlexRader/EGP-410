#pragma once


#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class SpawnDynamicArrive :public GameMessage
{
public:
	SpawnDynamicArrive(const Vector2D& pos);
	~SpawnDynamicArrive();

	void process();

private:
	Vector2D mPos;
};