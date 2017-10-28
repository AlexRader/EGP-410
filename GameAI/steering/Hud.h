#pragma once


#include "Trackable.h"
#include <allegro5/allegro.h>
#include <string>

class GraphicsBuffer;

const ALLEGRO_COLOR RED_COLOR = al_map_rgb(255, 50, 25);

class Hud : public Trackable
{
public:
	Hud();
	~Hud();

	void draw();

	void update(float time);

private:
	std::string mPlus, mMinus, mEnemyVelocity, mRadius, mAngularVelocity, 
				mBoids, mSeperation, mCohesion, mVMatch;
	int mSpacingVal;

};
