#include "KinematicUnit.h"
#include "SeperationSteering.h"
#include <algorithm> 

SeperationSteering::SeperationSteering(KinematicUnit* pMover)
	:mpMover(pMover)
	, mReaction(0.0f)
{
	setWeight(.5f);
}

//behavior to keep people seperated
Steering* SeperationSteering::getSteering()
{
	Vector2D direction;
	float distance;
	mReaction = gpGame->getUnitManager()->getRadius(); // sets the radius in which you check seperation

	//loops through all targets
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{
		direction = gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition();
		distance = direction.getLength();
		// if the distance calculated is less than the raction radius check stuff
		if (distance < mReaction)
		{
			mStrength = min(DECAY_COEFFICIENT_VAR / (distance * distance), mpMover->getMaxAcceleration());
			direction.normalize();

			mLinear += direction * mStrength;
		}
	}
	return this;
}