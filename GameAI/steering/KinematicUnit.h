#pragma once

#include "Kinematic.h"
#include "Steering.h"
#include <vector>
//#include "PlayerMoveToMessage.h"

/*KinematicUnit - a unit that is derived from the Kinematic class.  Adds behaviors and max speeds and a current Steering.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class Sprite;
class GraphicsBuffer;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

//minmimum forward speed a unit has to have inorder to rotate 
//(keeps unit from spinning in place after stopping
const float MIN_VELOCITY_TO_TURN_SQUARED = 1.0f;

class KinematicUnit: public Kinematic
{
public:
	KinematicUnit( Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, std::string name, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f );
	~KinematicUnit();

	//getters and setters
	void setTarget( const Vector2D& target ) { mTarget = target; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	Vector2D getTarget() const { return mTarget; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	void setVelocity( const Vector2D& velocity ){ mVelocity = velocity; };
	void setVelocityMax(const float var) { if (mMaxVelocity + var > 0) mMaxVelocity += var; };

	virtual void setNewOrientation();//face the direction you are moving

	std::string getName() const { return mName; };
	Sprite* getSprite() const { return mpSprite; };
	// setting the timer to change directions
	void setRandom(const float var) { mRandomChange = var; };
	void setRandomNumber();
	Vector2D settingTarget();

	//draw yourself to the indicated buffer
	void draw( GraphicsBuffer* pBuffer );
	//move according to the current velocities and update velocities based on current Steering
	void update(float time);

	//initiate behaviors
	void seek( const Vector2D& target );
	void arrive( const Vector2D& target );
	void wander();
	void dynamicWander();
	void dynamicSeek( KinematicUnit* pTarget );
	void dynamicFlee( KinematicUnit* pTarget );
	void dynamicArrive( KinematicUnit* pTarget );
	void collisionAvoidence();
	void Seperation();
	void VelocityMatching();
	void Cohesion();

	/*
	//get the desired behaviors
	float getVMatching();
	float getCohesion();
	float getSeperation();*/

	//allows changes to be made to steering values
	void setVMatchingWeight(float var);
	void setCohesion(float var);
	void setSeperation(float var);

	inline int getSize() const { return mSteeringBehavior.size(); };

	void addSteeringBehavior(Steering* theSteering);
	Steering* getUnitSteering(int indexPos);
	void clean();
	void deleteUnit(unsigned int indexPos);
	//KinematicUnit* getUnit(int indexPos);
	void wallCollision();

	void inRange(bool isInRange);
	void checkDist();

private:
	std::vector<Steering*> mSteeringBehavior;
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	
	Vector2D mTarget;//used only for Kinematic seek and arrive
	float mMaxVelocity;
	float mMaxAcceleration;
	float mRandomChange;
	std::string mName;
	bool mInRange;
	void setSteering( Steering* pSteering );

};