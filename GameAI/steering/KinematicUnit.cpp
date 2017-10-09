#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"
#include "DynamicWanderSteering.h"
#include <stdio.h>
#include <math.h>
//#include "GameMessageManager.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, std::string name, float rotationVel, float maxVelocity, float maxAcceleration)
:Kinematic( position, orientation, velocity, rotationVel )
,mpSprite(pSprite)
,mpCurrentSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
,mName(name)
,mInRange(false)
,mRandomChange(0.0f)
{
	
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time)
{
	// this got updated
	Steering* steering;
	if( mpCurrentSteering != NULL )
	{
		if (mName != PLAYER) // this checks for enemy ai
		{
			//steering = mpCurrentSteering->getSteering();
			
			checkDist();
			/*mRandomChange -= time;
			// this entire function addition is to get wander to work
			// everytime you getSteering() for wander it changes the direction of the ai
			// basically it makes the ai freak out
			if (mRandomChange <= 0 && mInRange == false)
			{
				setRandomNumber();
				steering = mpCurrentSteering->getSteering();
			}
			else if (mInRange == true)
				steering = mpCurrentSteering->getSteering();
			else
			{
				steering = mpCurrentSteering;
				//steering = trunc(steering);
				
			}*/
		}
		//else
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}
	
	if( steering->shouldApplyDirectly() && mName == PLAYER)
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}
	
	wallCollision();
	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );
	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	setNewOrientation();
	
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicWander()
{
	DynamicWanderSteering* pDynamicWanderSteering = new DynamicWanderSteering(this);
	setSteering(pDynamicWanderSteering);
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getUnitManager()->getPlayer());
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getUnitManager()->getPlayer(), true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, gpGame->getUnitManager()->getPlayer());
	setSteering( pDynamicArriveSteering );
}


void KinematicUnit::setRandomNumber()
{
	setRandom(((float)(rand() % 4 + 1)));
}


// setting the target after direction change
Vector2D KinematicUnit::settingTarget()
{ 
	int xVal, yVal;
	xVal = rand() % gpGame->getGraphicsSystem()->getWidth();
	yVal = rand() % gpGame->getGraphicsSystem()->getHeight();
	return Vector2D(xVal, yVal);
}

// if player is in range do stuff
void KinematicUnit::inRange(bool isInRange)
{
	if (mInRange == true && isInRange == false)
	{
		this->dynamicWander();
		mpCurrentSteering->getSteering();
		mInRange = false;
	}
	else if (mInRange == false && isInRange == true)
	{
		if (mName == DYNAMIC_ARRIVE)
			this->dynamicFlee(gpGame->getUnitManager()->getPlayer());
		else
			this->dynamicSeek(gpGame->getUnitManager()->getPlayer());
		mInRange = true;
	}
}

//checks if player is in range
void KinematicUnit::checkDist()
{
	if ((gpGame->getUnitManager()->getPlayer()->getPosition() - getPosition()).getLength() <= gpGame->getUnitManager()->getRadius())
		inRange(true);
	else
		inRange(false);
}


void KinematicUnit::wallCollision()
{
	Vector2D var;
	Vector2D pos;
	for (int i = 0; i < gpGame->getUnitManager()->getSizeWall(); i++)
	{
		var = gpGame->getUnitManager()->getUnitWall(i)->getPosition();
		if (gpGame->getUnitManager()->getUnitWall(i)->getName() == WALL_HOR)
		{
			if (this->getPosition().getY() >= var.getY() && this->getPosition().getY() <= var.getY() + (gpGame->getUnitManager()->getUnitWall(i)->getSprite()->getHeight()))
			{
				this->setVelocity(Vector2D(this->getVelocity().getX(), (this->getVelocity().getY() * -1)));
			}
		}
		else
		{
			if (this->getPosition().getX() >= var.getX() && this->getPosition().getX() <= var.getX() + gpGame->getUnitManager()->getUnitWall(i)->getSprite()->getWidth())
				this->setVelocity(Vector2D((this->getVelocity().getX() * -1), this->getVelocity().getY()));
		}
	}
}