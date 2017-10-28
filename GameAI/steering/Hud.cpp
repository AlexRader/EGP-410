#include "Game.h"
#include "Hud.h"
#include <sstream>


Hud::Hud()
:mPlus("+: Increases value")
,mMinus("-: Decreases Value")
,mEnemyVelocity("V: Enemy Velocity Control")
,mRadius("R: Detection Radius")
,mAngularVelocity("A: Angular Velocity")
,mBoids("I: spawn 5 Boids")
,mCohesion("C: Modify Cohesion weight")
,mSeperation("S: Modify Seperation weight")
,mVMatch("X: Modify Velocity Matching weight")
,mSpacingVal(20)
{
}

Hud::~Hud()
{

}
// drawing the current values for properties
void Hud::draw()
{
	std::stringstream radius;
	std::stringstream velocity;
	std::stringstream angularVel;
	std::stringstream cohesion;
	std::stringstream seperation;
	std::stringstream velocityMatch;
	radius << gpGame->getUnitManager()->getRadius();

	if (gpGame->getUnitManager()->getSize() != 0)
	{
		velocity << gpGame->getUnitManager()->getUnit(0)->getMaxVelocity();
		angularVel << gpGame->getUnitManager()->getUnit(0)->getRotationVel();
		velocityMatch << gpGame->getUnitManager()->getUnit(0)->getUnitSteering(1)->getWeight();
		seperation << gpGame->getUnitManager()->getUnit(0)->getUnitSteering(2)->getWeight();
		cohesion << gpGame->getUnitManager()->getUnit(0)->getUnitSteering(3)->getWeight();
	}
	else
	{
		velocity << " ";
		angularVel << " ";
		velocityMatch << " ";
		seperation << " ";
		cohesion << " ";
	}

	std::string val = mRadius +  " " + radius.str().c_str();
	std::string enemyVal = mEnemyVelocity + " " + velocity.str().c_str();
	std::string angularVelocity = mAngularVelocity + " " + angularVel.str().c_str();
	std::string vMatch = mVMatch + " " + velocityMatch.str().c_str();
	std::string sep = mSeperation + " " + seperation.str().c_str();
	std::string coh = mCohesion + " " + cohesion.str().c_str();


	//al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());
	//al_draw_text(gpGame->getFont(), RED_COLOR, 500, mSpacingVal, ALLEGRO_ALIGN_CENTRE, mPlus.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal, ALLEGRO_ALIGN_LEFT, mPlus.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 2, ALLEGRO_ALIGN_LEFT, mMinus.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 3, ALLEGRO_ALIGN_LEFT, enemyVal.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 4, ALLEGRO_ALIGN_LEFT, val.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 5, ALLEGRO_ALIGN_LEFT, angularVelocity.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 6, ALLEGRO_ALIGN_LEFT, mBoids.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 7, ALLEGRO_ALIGN_LEFT, vMatch.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 8, ALLEGRO_ALIGN_LEFT, sep.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 9, ALLEGRO_ALIGN_LEFT, coh.c_str());

	
}

void Hud::update(float time)
{

}
