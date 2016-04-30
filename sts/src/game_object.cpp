#include "game_object.hpp"

#include <OGRE/OgreRoot.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "game_data.hpp"
#include "sts_resources.hpp"

namespace sts {
    UnitType::UnitType(std::string _id, Entity *_entityPtr, int hm, int sm, const Weapon *w1, const Weapon *w2)
            : id(_id), entityPtr(_entityPtr), healthMax(hm), speedMax(sm), weapon1(w1), weapon2(w2)
    { Ogre::LogManager::getSingleton().logMessage("UnitType created"); }

    boost::filesystem::path Level::configs_path = boost::filesystem::path(sts::getDataBasePath()) /
            boost::filesystem::path("text") / boost::filesystem::path("levels");

    Unit::Unit(int x, int y, double d, UnitType *utptr, std::list<State> states) : LayeredObject(x, y, d) {

    }

    Level::Level(std::string level_json_name) {
        pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path(level_json_name)).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &mfs_root : root)
        {
            assert(mfs_root.first.empty()); // lists have no keys
            pt::ptree mfs_tree = mfs_root.second;

            Ogre::LogManager::getSingleton().logMessage("Enemy loaded");
            std::string unit_type_name = mfs_tree.get<std::string>("type");
            const UnitType *unitType = GameData::unit_types[unit_type_name];
            int x = mfs_tree.get<int>("x0");
            int y = mfs_tree.get<int>("y0");
            double d = mfs_tree.get<int>("y0");
            std::list<State> states = parseStates(mfs_tree.get_child("states"));

        }
        std::cout << "FFFFFFFFFFFFFFFFFFFFFFFf" << std::endl;
    }

    std::list<State> Level::parseStates(pt::ptree root) {
        std::list<State> states;
        for (pt::ptree::value_type &state : root) {
            assert(state.first.empty()); // lists have no keys
            pt::ptree state_tree = state.second;
            std::string state_type = state_tree.get<std::string>("type");
            std::cout << state_type << std::endl;
        }
        return states;
    }
}