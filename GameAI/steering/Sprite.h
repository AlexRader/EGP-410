#pragma once

#include <string>

/*Sprite - a logical portion of a GraphicsBuffer.

Dean Lawson
Champlain College
2011
*/
#include <allegro5/allegro.h>

#include "Trackable.h"

class GraphicsBuffer;

class Sprite:public Trackable
{
public:
	Sprite( GraphicsBuffer* pBuffer, float srcX, float srcY, float width, float height );
	~Sprite();

	//draw the contents of the sprite to a GraphicsBuffer - may be rotated
	void draw( GraphicsBuffer& dest, float dx, float dy, float rotationInRadians = 0, int flags = 0 );

	// added these to get the width and height of sprites which will be usefull in collision
	inline int getWidth() { return mWidth; };
	inline int getHeight() { return mHeight; };

private:
ALLEGRO_BITMAP* mpBitmap;//subBitmap based off the GraphicsBuffer object is contructed with
	int mWidth;
	int mHeight;
};