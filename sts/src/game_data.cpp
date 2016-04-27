#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "game_data.hpp"
#include "sts_resources.hpp"

namespace sts {
    namespace pt = boost::property_tree;

    GameData::GameData() : configs_path(sts::getDataBasePath()) {
        configs_path = configs_path / boost::filesystem::path("text");

        parseMuzzleFlashStyles();
    }

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
            MuzzleFlashStyle mfs(id, colormap_hue, sound);
            muzzleFlashStyles[id] = mfs;
        }
    }
}