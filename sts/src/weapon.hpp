#pragma once

#include <OGRE/OgreRoot.h>

#include <string>
#include "bullet.hpp"

namespace sts {

struct MuzzleFlashStyle {
    MuzzleFlashStyle(const std::string &_id, const std::string &_colormap_hue, const std::string &_sound)
            : id(_id), colormap_hue(_colormap_hue), sound(_sound) {}
    std::string id;
    /* convert to hex immediately? */
    std::string colormap_hue;
    std::string sound;
};

class Weapon {
public:
    Weapon(const std::string &_id, const IBulletStyle *ibs, const MuzzleFlashStyle *mfs, int d, bool isH) :
            id(_id), bulletStylePtr(ibs), muzzleFlashStylePtr(mfs), damage(d), isHoming(isH) {
        Ogre::LogManager::getSingleton().logMessage("Weapon created");
    }

    std::string id;
    const IBulletStyle *bulletStylePtr;
    const MuzzleFlashStyle *muzzleFlashStylePtr;
    int damage;
    bool isHoming;
};

}

