#pragma once
#include "EventListener.h"
#include "Trackable.h"
#include "KinematicUnit.h"
#include <map>

class UnitManager : public EventListener
{
public:
	UnitManager();
	~UnitManager();

	// these need to be changed to work with current kinematic unit
	/*
	void addUnit(Vector2D loc);
	void addUnit(Vector2D loc, Vector2D vel, std::string name);
	void deleteUnit(int indexPos);
	void deleteUnit(KinematicUnit* unit);*/
	KinematicUnit* getUnit(int indexPos);

	//KinematicUnitUnit * checkHit(int x, int y);
	void clear();

	void update(float dt);
	//void draw();

	//void pause();

	//will need to be changed
	//void handleEvent(const Event& theEvent);

	//void checkOut();

private:
	std::map<int, KinematicUnit*> mUnits;
	bool mPause;
	int mNumOfUnits;
};




