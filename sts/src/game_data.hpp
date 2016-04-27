#include <iostream>
#include <unordered_map>
#include <boost/filesystem.hpp>

namespace sts {
    struct MuzzleFlashStyle {
        MuzzleFlashStyle() {}
        MuzzleFlashStyle(const std::string &_id, const std::string &_colormap_hue, const std::string &_sound)
                : id(_id), colormap_hue(_colormap_hue), sound(_sound) {}
        std::string id;
        /* convert to hex immediately? */
        std::string colormap_hue;
        std::string sound;
    };

    /* Stores all the not-level-specific game data */
    class GameData {
    public:
        /* read jsons and load data */
        GameData();
        std::unordered_map<std::string, MuzzleFlashStyle> muzzleFlashStyles;
    private:
        boost::filesystem::path configs_path;

        void parseMuzzleFlashStyles();
    };
}
