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

private:
	KinematicUnit* mpMover;
	float mReaction, mDistance, mStrength;
	Vector2D mDirection; 
};

