#pragma once
#include "EventListener.h"
#include "Trackable.h"
#include "KinematicUnit.h"
#include <map>

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	// these need to be changed to work with current kinematic unit
	
	void addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, std::string name, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	//void addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f, estd::string name);
	void deleteUnit(int indexPos);
/*	void deleteUnit(KinematicUnit* unit);*/
	KinematicUnit* getUnit(int indexPos);

	//KinematicUnitUnit * checkHit(int x, int y);
	void clear();

	void update(float dt);
	void draw(GraphicsBuffer* pBuffer);

	inline int getUnitsLeft() const { return mUnitsLeft; };

	inline int getNumOfUnits() const { return mNumOfUnits; };

	inline int getSize() const { return mUnits.size(); };

	bool findNearestSequentialUnit();

	//void pause();

	//will need to be changed
	//void handleEvent(const Event& theEvent);

	//void checkOut();

private:
	std::map<int, KinematicUnit*> mUnits;
	bool mPause;
	int mNumOfUnits;
	int mUnitsLeft;
};




