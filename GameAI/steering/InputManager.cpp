
#include "Game.h"
#include "Defines.h"
#include "InputManager.h"
#include <allegro5/allegro.h>
#include "GameMessageManager.h"
#include <sstream>
#include "PlayerMoveToMessage.h"
#include "SpawnDynamicArrive.h"
#include "SpawnDynamicSeek.h"
#include "RemoveAi.h"
#include "DisplayDebug.h"
#include "RadiusChange.h"
#include "AngularControl.h"
#include "EnemyVelocityControl.h"
#include "EscapeMessage.h"
#include "PlusMinusMessage.h"
#include "BoidSpawnMessage.h"
#include "WeightChange.h"

InputManager::InputManager()
{
	mInitialized = false;
}


InputManager::~InputManager()
{
	if (mInitialized)
		cleanUp();
}

void InputManager::init()
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
	mSwitched = 0.0f;
}

void InputManager::cleanUp()
{
	if (mInitialized)
	{
		mInitialized = false;
		al_uninstall_keyboard();
		al_uninstall_mouse();
	}
}

void InputManager::update()
{
	//get input - should be moved someplace better
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}



	//all this should be moved to InputManager!!!
	{
		//get mouse state
		ALLEGRO_MOUSE_STATE mouseState;
		al_get_mouse_state(&mouseState);

		//create mouse text
		std::stringstream mousePos;
		mousePos << mouseState.x << ":" << mouseState.y;

		//write text at mouse position
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());

		//get current keyboard state
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		al_get_keyboard_state(&mCurrentState);
		//if escape key was down then exit the loop
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			GameMessage* pMessage = new EscapeMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (al_key_down(&mCurrentState, ALLEGRO_KEY_I) && !al_key_down(&mPreviousState, ALLEGRO_KEY_I))
		{
			//Vector2D pos(gpGame->getUnitManager()->getSpawnPoint().
			Vector2D pos = gpGame->getSpawnPoint();

			GameMessage* pMessage = new BoidSpawnMessage(pos);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		 // theses next 3 functions just change value of the three weights for flocking
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_X) && !al_key_down(&mPreviousState, ALLEGRO_KEY_X))
		{
			GameMessage* pMessage = new WeightChange(2, mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (al_key_down(&mCurrentState, ALLEGRO_KEY_C) && !al_key_down(&mPreviousState, ALLEGRO_KEY_C))
		{
			GameMessage* pMessage = new WeightChange(3, mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (al_key_down(&mCurrentState, ALLEGRO_KEY_S) && !al_key_down(&mPreviousState, ALLEGRO_KEY_S))
		{
			GameMessage* pMessage = new WeightChange(4, mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_Q) && !al_key_down(&mPreviousState, ALLEGRO_KEY_Q))
		{
			GameMessage* pMessage = new WeightChange(5, mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		if (al_key_down(&mCurrentState, ALLEGRO_KEY_D) && !al_key_down(&mPreviousState, ALLEGRO_KEY_D))
		{
			GameMessage* pMessage = new RemoveAi();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_TILDE) && !al_key_down(&mPreviousState, ALLEGRO_KEY_TILDE))
		{
			GameMessage* pMessage = new DisplayDebug();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_EQUALS) && !al_key_down(&mPreviousState, ALLEGRO_KEY_EQUALS))
		{
			GameMessage* pMessage = new PlusMinusMessage(10.0f);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_MINUS) && !al_key_down(&mPreviousState, ALLEGRO_KEY_MINUS))
		{
			GameMessage* pMessage = new PlusMinusMessage(-10.0f);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_R) && !al_key_down(&mPreviousState, ALLEGRO_KEY_R))
		{
			GameMessage* pMessage = new RadiusChange(mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_V) && !al_key_down(&mPreviousState, ALLEGRO_KEY_V))
		{
			GameMessage* pMessage = new EnemyVelocityControl(mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_A) && !al_key_down(&mPreviousState, ALLEGRO_KEY_A))
		{
			GameMessage* pMessage = new AngularControl(mSwitched);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

		mPreviousState = mCurrentState;
	}
}
