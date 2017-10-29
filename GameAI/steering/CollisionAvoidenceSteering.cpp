#include "KinematicUnit.h"
#include "CollisionAvoidenceSteering.h"
#include <algorithm> 
#include "Game.h"
#include "Sprite.h"

CollisionAvoidenceSteering::CollisionAvoidenceSteering(KinematicUnit* pMover)
	:mpMover(pMover)
	, mLookAhead(3.0f)
	, mAvoidDistance(64.0f)
{
	setWeight(1.5f);
}


Steering* CollisionAvoidenceSteering::getSteering()
{
	Vector2D var;
	mRayVector = mpMover->getVelocity();
	mRayVector.normalize();
	mRayVector *= mLookAhead;
	for (int i = 0; i < gpGame->getUnitManager()->getSizeWall(); i++)
	{
		var = gpGame->getUnitManager()->getUnitWall(i)->getPosition();
		if (gpGame->getUnitManager()->getUnitWall(i)->getName() == WALL_HOR)
		{
			if (mRayVector.getY() >= var.getY() && mRayVector.getY() <= var.getY() + (gpGame->getUnitManager()->getUnitWall(i)->getSprite()->getHeight()))
			{
				//this->setVelocity(Vector2D(this->getVelocity().getX(), (this->getVelocity().getY() * -1)));
			}
		}
		else
		{
			if (mRayVector.getX() >= var.getX() && mRayVector.getX() <= var.getX() + gpGame->getUnitManager()->getUnitWall(i)->getSprite()->getWidth())
			{

			}
				//this->setVelocity(Vector2D((this->getVelocity().getX() * -1), this->getVelocity().getY()));
		}
	}

	/*
	float radius = 50.0f;
	float shortestTime = INFINITY;

	KinematicUnit* firstTarget = NULL;
	float firstMinimumSeperation = 0;
	float firstDistance = 0;
	Vector2D firstRelativePos = Vector2D(0.0f, 0.0f);
	Vector2D firstRelativeVel = Vector2D(0.0f, 0.0f);

	Vector2D relativePos;
	Vector2D relativeVel;
	float relativeSpeed;
	float timeToCollision;
	float distance;
	float minSeperation;

	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{
		relativePos = gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition();
		relativeVel = gpGame->getUnitManager()->getUnit(i)->getVelocity() - mpMover->getVelocity();
		relativeSpeed = relativeVel.getLength();
		timeToCollision = dot(relativePos, relativeVel) / (relativeSpeed * relativeSpeed);

		distance = relativePos.getLength();
		minSeperation = distance - relativeSpeed * timeToCollision;

		if (minSeperation > 2 * radius)
			continue;
		if (timeToCollision > 0 && timeToCollision < shortestTime)
		{
			shortestTime = timeToCollision;
			firstTarget = gpGame->getUnitManager()->getUnit(i);
			firstMinimumSeperation = minSeperation;
			firstDistance = distance;
			firstRelativePos = relativePos;
			firstRelativeVel = relativeVel;
		}

		if (!firstTarget)
			return NULL;
		if (firstMinimumSeperation <= 0 || distance < 2 * radius)
			relativePos = firstTarget->getPosition() - mpMover->getPosition();
		else
			relativePos = firstRelativePos + firstRelativePos * shortestTime;

		relativePos.normalize();
		mLinear = relativePos * gpGame->getUnitManager()->getUnit(0)->getMaxAcceleration();
	}
	return this;
	*/
}