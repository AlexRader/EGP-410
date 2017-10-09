
#include "game.h"
#include "eventSystem.h"
#include "event.h"
#include "ClickEvent.h"
#include "UnitManager.h"

UnitManager::UnitManager()
{
	mPause = false;
	mRadius = 20.0f;
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

	temp->dynamicWander();

	mUnits.push_back(temp);
}

void UnitManager::addUnitWall(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, std::string name, float maxVelocity, float maxAcceleration)
{
	KinematicUnit *temp = new KinematicUnit(pSprite, position, orientation, velocity, name, rotationVel, maxVelocity, maxAcceleration);
	mUnitsWall.push_back(temp);
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

KinematicUnit* UnitManager::getUnitWall(int indexPos)
{
	return mUnitsWall.at(indexPos);
}


void UnitManager::clear()
{

	for each (KinematicUnit* unit in mUnits)
		delete unit;
	
	mUnits.clear();

	for each (KinematicUnit* unit in mUnitsWall)
		delete unit;

	mUnitsWall.clear();

	delete mpPlayer;
}

void UnitManager::update(float dt)
{
	mpPlayer->update(dt);
	for each (KinematicUnit* unit in mUnits)
		unit->update(dt);
}


void UnitManager::draw(GraphicsBuffer* pBuffer)
{
	for each (KinematicUnit* unit in mUnitsWall)
		unit->draw(pBuffer);
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
