#pragma once

#include "Trackable.h"
#include "string.h"
#include "fstream"

const std::string FILE_NAME = "savedVariables";
class FileSystem : public Trackable
{
public:


private:
	std::ifstream fin;
	std::ofstream fout;

};
