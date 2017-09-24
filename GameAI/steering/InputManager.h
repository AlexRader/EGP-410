#pragma once


#include "Trackable.h"

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();

	void init();
	void cleanUp();

	void update();

private:
	bool mInitialized;
	ALLEGRO_KEYBOARD_STATE mPreviousState;
	ALLEGRO_KEYBOARD_STATE mCurrentState;

};

