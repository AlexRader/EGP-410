#pragma once

#include "Steering.h"
#include "Game.h"

class KinematicUnit;

const float DECAY_COEFFICIENT = 20.0f;

class CollisionAvoidenceSteering :public Steering
{
public:
	CollisionAvoidenceSteering(KinematicUnit* pMover);
	~CollisionAvoidenceSteering() {};

	virtual Steering* getSteering();

	//added this in just for collision avoidence
	float dot(Vector2D& v1, Vector2D& v2) { return v1.getX() * v2.getX() + v1.getY() * v2.getY(); };

private:
	KinematicUnit* mpMover;
	float mLookAhead, mAvoidDistance, mStrength;
	Vector2D mRayVector; 
};

