#include "KinematicUnit.h"
#include "CohesionSteering.h"
#include <algorithm> 

CohesionSteering::CohesionSteering(KinematicUnit* pMover)
	:mpMover(pMover)
	, mReaction(0.0f)
{
	setWeight(1.0f);
}

//behavior to keep people seperated
Steering* CohesionSteering::getSteering()
{
	Vector2D direction = Vector2D(0.0f, 0.0f);
	Vector2D centerOfMass = Vector2D(0.0f, 0.0f);
	int neighbors = 0;
	float distance;
	mReaction = gpGame->getUnitManager()->getRadius() + ADDED_RANGE; // sets the radius in which you check cohesion

	//loops through all targets
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{
		direction = gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition();
		distance = direction.getLength();
		// if the distance calculated is less than the raction radius change center of mass
		if (distance < mReaction)
		{
			centerOfMass += gpGame->getUnitManager()->getUnit(i)->getPosition();
			neighbors++;
			mStrength = min(DECAY_COEFFICIENT_VARIENT / (distance * distance), mpMover->getMaxAcceleration());
			direction.normalize();

			mLinear += direction * mStrength;
		}
	}
	// calculates the cohesion to the center of mass
	if (neighbors > 0)
	{
		centerOfMass /= neighbors;
		mLinear += centerOfMass - mpMover->getPosition();
		mLinear.normalize();
	}
	
	return this;
}