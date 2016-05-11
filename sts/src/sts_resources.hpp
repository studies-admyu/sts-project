#pragma once

#include <list>
#include <string>

namespace sts {

/** Returns data path for different platforms */
std::string getDataBasePath();

/** Returns data directories */
std::list<std::string> getDataDirs();

}
