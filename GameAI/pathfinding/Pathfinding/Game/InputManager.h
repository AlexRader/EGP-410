#pragma once

#include "Trackable.h"
#include <allegro5/allegro.h>

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();

	void init();
	void cleanUp();

	void update();

	inline void setSwitch(float var) { mSwitched = var; };

private:
	bool mInitialized;
	float mSwitched;
	ALLEGRO_KEYBOARD_STATE mPreviousState;
	ALLEGRO_KEYBOARD_STATE mCurrentState;

	GameApp* pGame;

};