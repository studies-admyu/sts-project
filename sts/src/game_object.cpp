#include "game_object.hpp"

#include <OGRE/OgreRoot.h>
#include <boost/property_tree/json_parser.hpp>

#include "game_data.hpp"
#include "sts_resources.hpp"

namespace sts {

boost::filesystem::path Level::configs_path =
	boost::filesystem::path(sts::getDataBasePath()) /
	boost::filesystem::path("text") / boost::filesystem::path("levels");

Level::Level(std::string level_json_name)
{
	pt::ptree root;
	auto json_filename = (configs_path / boost::filesystem::path(level_json_name)).string();
	pt::read_json(json_filename, root);

	for (pt::ptree::value_type &unitRoot : root) {
		assert(unitRoot.first.empty()); // lists have no keys
		pt::ptree mfs_tree = unitRoot.second;

		Ogre::LogManager::getSingleton().logMessage("Enemy loaded");
		std::string unit_type_name = mfs_tree.get<std::string>("type");
		const UnitType *unitType = GameData::unit_types[unit_type_name];
		int x = mfs_tree.get<int>("x0");
		int y = mfs_tree.get<int>("y0");
		double d = mfs_tree.get<int>("y0");
		std::list<SM::State*> states = parseStates(mfs_tree.get_child("states"));
		/** @todo Fix this */
		/* units.push_back(Unit(x, y, d, unitType, states)); */
	}
}

std::list<SM::State*> Level::parseStates(pt::ptree root)
{
	std::list<SM::State*> states;
	for (pt::ptree::value_type &state : root) {
		assert(state.first.empty()); // lists have no keys
		pt::ptree state_tree = state.second;
		states.push_back(parseState(state_tree));
	}
	return states;
}

SM::State* Level::parseState(pt::ptree tree)
{
	std::string state_type = tree.get<std::string>("type");
	std::cout << "Parsing state " << state_type << std::endl;
	return nullptr;
	/* return SM::State(); */
}

} // namespace sts
