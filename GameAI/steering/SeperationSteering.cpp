#include "KinematicUnit.h"
#include "SeperationSteering.h"
#include <algorithm> 

SeperationSteering::SeperationSteering(KinematicUnit* pMover)
	:mpMover(pMover)
	, mReaction(64.0f)
{
	setWeight(.5f);
}


Steering* SeperationSteering::getSteering()
{
	Vector2D direction;
	float distance;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{
		direction = gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition();
		distance = direction.getLength();
		if (distance < mReaction)
		{
			mStrength = min(DECAY_COEFFICIENT_VAR / (distance * distance), mpMover->getMaxAcceleration());
			direction.normalize();

			mLinear += direction * mStrength;
		}
	}
	return this;
}