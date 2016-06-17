#include "game_data.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "sts_resources.hpp"
#include "bullet.hpp"
#include "weapon.hpp"
#include "game_object.hpp"

namespace sts {
    namespace pt = boost::property_tree;

    boost::filesystem::path GameData::configs_path;

    std::unordered_map<std::string, MuzzleFlashStyle*> GameData::muzzleFlashStyles;
    std::unordered_map<std::string, Renderable*> GameData::renderables;
    std::unordered_map<std::string, IBulletStyle*> GameData::bulletStyles;
    std::unordered_map<std::string, Weapon*> GameData::weapons;
    std::unordered_map<std::string, UnitType*> GameData::unit_types;

    void GameData::load() {
        configs_path = sts::getDataBasePath();
        configs_path = configs_path / boost::filesystem::path("text");

        parseMuzzleFlashStyles();
        parseEntities();
	    parseBulletStyles();
        parseWeapons();
        parseUnitTypes();
    }

    void GameData::parseMuzzleFlashStyles() {
        /** @todo Handle exceptions */
	pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path("muzzle_flash_styles.json")).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &mfs_root : root)
        {
            assert(mfs_root.first.empty()); // lists have no keys
            pt::ptree mfs_tree = mfs_root.second;
            std::string id = mfs_tree.get<std::string>("id");
            std::string colormap_hue = mfs_tree.get<std::string>("colormap.hue");
            std::string sound = mfs_tree.get<std::string>("sound");
            std::cout << "Read muzzle flash style with id " << id << std::endl;
            muzzleFlashStyles[id] = new MuzzleFlashStyle(id, colormap_hue, sound);
        }
    }

    void GameData::parseEntities() {
        /** @todo Handle exceptions */
        pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path("entities.json")).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &eRoot : root)
        {
            assert(eRoot.first.empty()); // lists have no keys
            pt::ptree renderableTree = eRoot.second;
            std::string id = renderableTree.get<std::string>("id");
            std::string colormap_hue = renderableTree.get<std::string>("colormap.hue");
            std::string model_name = renderableTree.get<std::string>("model");
            std::cout << "Read renderable with id " << id << std::endl;
            /** @todo Fix the resource addition */
            /* entities[id] = new Entity(id, model_name, colormap_hue); */
        }
    }

	// Creates mappings BulletStyleName -> instance of needed BulletStyles. All BulletStyles are singltones
    void GameData::parseBulletStyles() {
        bulletStyles["RoundBullet"] = RoundBullet::getInstance();
        bulletStyles["BlastBullet"] = BlastBullet::getInstance();
    }

    // Creates mappings weapon id -> instance of Weapon with specified in json params
    void GameData::parseWeapons() {
        pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path("weapons.json")).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &wRoot : root)
        {
            assert(wRoot.first.empty()); // lists have no keys
            pt::ptree weaponTree = wRoot.second;
            std::string id = weaponTree.get<std::string>("id");
            weapons[id] = new Weapon(weaponTree);
        }
    }

    void GameData::parseUnitTypes() {
        pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path("unit_types.json")).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &utRoot : root)
        {
            assert(utRoot.first.empty()); // lists have no keys
            pt::ptree unitTypeTree = utRoot.second;
            std::string id = unitTypeTree.get<std::string>("id");
            std::string renderable_name = unitTypeTree.get<std::string>("entity");
            std::string weapon1_name = unitTypeTree.get<std::string>("weapon1");
            std::string weapon2_name = unitTypeTree.get<std::string>("weapon2");
            int health_max = unitTypeTree.get<int>("health_max");
            int speed_max = unitTypeTree.get<int>("speed_max");
            /** @todo Fix the resource addition */
            /* unit_types[id] = new UnitType(id, renderables[entity_name], health_max, speed_max, weapons[weapon1_name],
            weapons[weapon2_name]); */
        }
    }

}
