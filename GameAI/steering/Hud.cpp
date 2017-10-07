#include "Game.h"
#include "Hud.h"
#include <sstream>


Hud::Hud()
:mPlus("+: Increases value")
,mMinus("-: Decreases Value")
,mEnemyVelocity("V: Enemy Velocity Control")
,mRadius("R: Detection Radius")
,mAngularVelocity("A: Angular Velocity")
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

	radius << gpGame->getUnitManager()->getRadius();

	if (gpGame->getUnitManager()->getSize() != 0)
	{
		velocity << gpGame->getUnitManager()->getUnit(0)->getMaxVelocity();
		angularVel << gpGame->getUnitManager()->getUnit(0)->getRotationVel();
	}
	else
	{
		velocity << " ";
		angularVel << " ";
	}

	std::string val = mRadius +  " " + radius.str().c_str();
	std::string enemyVal = mEnemyVelocity + " " + velocity.str().c_str();
	std::string angularVelocity = mAngularVelocity + " " + angularVel.str().c_str();

	//al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());
	//al_draw_text(gpGame->getFont(), RED_COLOR, 500, mSpacingVal, ALLEGRO_ALIGN_CENTRE, mPlus.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal, ALLEGRO_ALIGN_LEFT, mPlus.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 2, ALLEGRO_ALIGN_LEFT, mMinus.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 3, ALLEGRO_ALIGN_LEFT, enemyVal.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 4, ALLEGRO_ALIGN_LEFT, val.c_str());
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 50, 25), 5, mSpacingVal * 5, ALLEGRO_ALIGN_LEFT, angularVelocity.c_str());

	
}

void Hud::update(float time)
{

}
