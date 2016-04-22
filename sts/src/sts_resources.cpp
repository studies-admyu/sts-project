#include "sts.hpp"

#include <OGRE/OgrePlatform.h>

namespace sts {

std::string getDataBasePath()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	return std::string("data/");
#else
	return std::string("../data/");
#endif
}

std::list<std::string> getDataDirs()
{
	std::list<std::string> returnResult;

	returnResult.push_back("materials");
	returnResult.push_back("materials/sprites");
	returnResult.push_back("materials/textures");
	returnResult.push_back("models");

	return returnResult;
}

}
