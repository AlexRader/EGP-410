#include "InputSystem.h"
#include "Game.h"
#include "EventSystem.h"
#include "ClickEvent.h"

InputSystem::InputSystem()
{
	mInitialized = false;
}

InputSystem::~InputSystem()
{
	if (mInitialized)
		cleanUp();
}

void InputSystem::init()
{
	if (mInitialized)
		cleanUp();

	//initialize systems
	if (!al_init())
	{
		std::cout << "This could be a problem... Allegro didn't initialize properly.\n";
	}

	if (!al_install_keyboard())
	{
		std::cout << "This could be a problem... Allegro couldn't initialize the keyboard.\n";
	}

	if (!al_install_mouse())
	{
		std::cout << "This could be a problem... Allegro couldn't initialize the Mouse addon.\n";
	}

	mInitialized = true;
}

void InputSystem::cleanUp()
{
	if (mInitialized)
	{
		mInitialized = false;
		al_uninstall_keyboard();
		al_uninstall_mouse();
	}
}

void InputSystem::update()
{
	//Game* pGame = Game::getGraphicsSystem();
	//Game* pGame = GRAPHICS_SYSTEM;
	
	GraphicsBufferManager* pBufferManager = gpGame->getGraphicsBufferManager();
		
		
		//pGame->getManagerBuffer();
	UnitManager* pUnitManager = gpGame->getUnitManager();
	al_get_keyboard_state(&mCurrentState);
	al_get_mouse_state(&mCurrentMouseState);

	if (al_key_down(&mCurrentState, ALLEGRO_KEY_ESCAPE) && !al_key_down(&mPreviousState, ALLEGRO_KEY_ESCAPE))
	{
		//gpGame->escapeSwitch();
	}

	if (al_key_down(&mCurrentState, ALLEGRO_KEY_SPACE) && !al_key_down(&mPreviousState, ALLEGRO_KEY_SPACE))
	{
		//gpGame->getManagerUnit()->pause();
	}

	/*
	if (mCurrentMouseState.x > 0 && mCurrentMouseState.x <  gpGame->getGraphicsSystem()->getWidth() &&
		mCurrentMouseState.y > 0 && mCurrentMouseState.y <  gpGame->getGraphicsSystem()->getHeight())
	{
		if (al_mouse_button_down(&mCurrentMouseState, 1) && !al_mouse_button_down(&mPreviousMouseState, 1))
		{
			gpEventSystem->fireEvent(ClickEvent(mCurrentMouseState.x, mCurrentMouseState.y));
		}
	}*/
	
	mPreviousState = mCurrentState;
	mPreviousMouseState = mCurrentMouseState;
}