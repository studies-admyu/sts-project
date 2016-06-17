#pragma once

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>

#include "gameplay/sts_unit.hpp"

namespace sts {

namespace pt = boost::property_tree;

class Level
{
public:
	Level(std::string level_json_name);
	static boost::filesystem::path configs_path;
	static std::list<State> parseStates(pt::ptree);
	static State parseState(pt::ptree);

	std::list<Unit> units;
};

} // namespace sts
