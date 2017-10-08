
#include "game.h"
#include "eventSystem.h"
#include "event.h"
#include "ClickEvent.h"
#include "UnitManager.h"

UnitManager::UnitManager()
{
	mPause = false;
	mRadius = 200.0f;
	//gpEventSystem->addListener(CLICK_EVENT, this);
}

UnitManager::~UnitManager()
{
	clear();
}

void UnitManager::addUnitPlayer(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, std::string name, float maxVelocity, float maxAcceleration)
{
	mpPlayer = new KinematicUnit(pSprite, position, orientation, velocity, name, rotationVel, maxVelocity, maxAcceleration);
}

void UnitManager::addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, std::string name, float maxVelocity, float maxAcceleration)
{
	KinematicUnit *temp = new KinematicUnit(pSprite, position, orientation, velocity, name, rotationVel, maxVelocity, maxAcceleration);

	temp->wander(getPlayer()->settingTarget());
	

	mUnits.push_back(temp);
}

void UnitManager::deleteUnit(unsigned int indexPos)
{
	if (indexPos < 0 || indexPos >= mUnits.size())
		return;
	delete mUnits.at(indexPos);
	mUnits.erase(mUnits.begin() + indexPos);
}

KinematicUnit* UnitManager::getUnit(int indexPos)
{
		return mUnits.at(indexPos);
}

void UnitManager::clear()
{

	for each (KinematicUnit* unit in mUnits)
		delete unit;
	
	mUnits.clear();
	delete mpPlayer;
}

void UnitManager::update(float dt)
{
	/*
	std::map<int, KinematicUnit*>::iterator iter;
	iter = mUnits.begin();

	if (mPause != true)
	{
		while (iter != mUnits.end())
		{
			iter->second->update(dt);
			iter++;
		}
	}
*/
	mpPlayer->update(dt);
	for each (KinematicUnit* unit in mUnits)
		unit->update(dt);
	//checkOut();

}


void UnitManager::draw(GraphicsBuffer* pBuffer)
{
	/*
	std::map<int, KinematicUnit*>::iterator iter;
	iter = mUnits.begin();

	while (iter != mUnits.end())
	{
		iter->second->draw(pBuffer);
		iter++;
	}
*/
	mpPlayer->draw(pBuffer);
	for each (KinematicUnit* unit in mUnits)
		unit->draw(pBuffer);
}

void UnitManager::setEnemyVelocity(float val)
{
	for each (KinematicUnit* unit in mUnits)
		unit->setVelocityMax(val);
}

void UnitManager::setAngularVelocity(float val)
{
	mpPlayer->setRotationalVelocitySecond(val);
	for each (KinematicUnit* unit in mUnits)
		unit->setRotationalVelocitySecond(val);
}
