#include "game_data.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "sts_resources.hpp"
#include "bullet.hpp"
#include "weapon.hpp"

namespace sts {
    namespace pt = boost::property_tree;

    boost::filesystem::path GameData::configs_path;

    std::unordered_map<std::string, MuzzleFlashStyle*> GameData::muzzleFlashStyles;
    std::unordered_map<std::string, Entity*> GameData::entities;
    std::unordered_map<std::string, IBulletStyle*> GameData::bulletStyles;
    std::unordered_map<std::string, Weapon*> GameData::weapons;

    void GameData::load() {
        configs_path = sts::getDataBasePath();
        configs_path = configs_path / boost::filesystem::path("text");

        parseMuzzleFlashStyles();
        parseEntities();
	    parseBulletStyles();
        parseWeapons();
    }

	// TODO: handle exceptions
    void GameData::parseMuzzleFlashStyles() {
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

	// TODO: handle exceptions
	void GameData::parseEntities() {
        pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path("entities.json")).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &mfs_root : root)
        {
            assert(mfs_root.first.empty()); // lists have no keys
            pt::ptree mfs_tree = mfs_root.second;
            std::string id = mfs_tree.get<std::string>("id");
            std::string colormap_hue = mfs_tree.get<std::string>("colormap.hue");
            std::string model_name = mfs_tree.get<std::string>("model");
            std::cout << "Read entity with id " << id << std::endl;
            entities[id] = new Entity(id, model_name, colormap_hue);
        }
    }

	// A stub which creates one instance of each IBulletStyle descendant.
    // Later we will configure bullet styles externally.
	void GameData::parseBulletStyles() {
        bulletStyles["RoundBullet"] = new RoundBullet();
        bulletStyles["BlastBullet"] = new BlastBullet();
	}

    void GameData::parseWeapons() {
        pt::ptree root;
        auto json_filename = (configs_path / boost::filesystem::path("weapons.json")).string();
        pt::read_json(json_filename, root);

        for (pt::ptree::value_type &mfs_root : root)
        {
            assert(mfs_root.first.empty()); // lists have no keys
            pt::ptree mfs_tree = mfs_root.second;
            std::string id = mfs_tree.get<std::string>("id");
            std::string bullet_style_name = mfs_tree.get<std::string>("bullet-style");
            std::string muzzle_flash_style_name = mfs_tree.get<std::string>("muzzle-flash-style");
            int damage = mfs_tree.get<int>("damage");
            bool isHoming = mfs_tree.get<bool>("homing");
            weapons[id] = new Weapon(id, bulletStyles[bullet_style_name],
                                           muzzleFlashStyles[muzzle_flash_style_name], damage, isHoming);
        }
    }
}