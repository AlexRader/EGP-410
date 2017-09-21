#pragma once


#include "Trackable.h"
#include "Defines.h"
#include <allegro5/allegro.h>

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanUp();

	void update();

private:
	ALLEGRO_KEYBOARD_STATE mPreviousState;
	ALLEGRO_MOUSE_STATE mPreviousMouseState;

	ALLEGRO_KEYBOARD_STATE mCurrentState;
	ALLEGRO_MOUSE_STATE mCurrentMouseState;
	bool mInitialized;
};

