#pragma once


#include "GameMessage.h"
#include "string.h"
#include "Vector2D.h"

class Vector2D;

class WeightChange :public GameMessage
{
public:
	WeightChange(int choice, float var);
	~WeightChange();

	void process();

private:
	Vector2D mPos;
	int mChoice;
	float mVar;
};