#pragma once

#include <string>

typedef int IDType;
typedef std::string IDDescriptor;

const IDType INVALID_ID = -1;

const IDType HIGHEST_ID = 9999;

//defines for different creation objects
const std::string PLAYER					= "Player";
const std::string DYNAMIC_ARRIVE  = "DynamicArrive";
const std::string DYNAMIC_SEEK		= "DynamicSeek";
const std::string WALL_VERT = "WallVert";
const std::string WALL_HOR = "WallHor";



#define MESSAGE_MANAGER gpGame->getMessageManager()
#define GRAPHICS_SYSTEM gpGame->getGraphicsSystem()