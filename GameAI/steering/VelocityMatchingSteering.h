#pragma once

#include "Steering.h"
#include "Game.h"

class KinematicUnit;

const float TIME_TO_TARGET = .1f;

class VelocityMatchingSteering :public Steering
{
public:
	VelocityMatchingSteering(KinematicUnit* pMover);
	~VelocityMatchingSteering() {};

	virtual Steering* getSteering();

	//added this in just for collision avoidence
	float dot(Vector2D& v1, Vector2D& v2) { return v1.getX() * v2.getX() + v1.getY() * v2.getY(); };

private:
	KinematicUnit* mpMover;
	float mRadius;
	Vector2D mStored;
	int mCount;
};