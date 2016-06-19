#pragma once

#include <exception>

#include <boost/property_tree/ptree.hpp>

#include <sts_cross_platform.hpp>

#include "sts_bullet_style.hpp"

namespace sts {

namespace pt = boost::property_tree;

/**
  * Weapon defines information about weapon: it' damage, BulletStyle, animations, etc, but it doesn't make
  * decisions when and where to shot. It also creates bullets.
  * It is jsonified, but each weapon is instantiated only once since it doesn't need SceneObject specific state
  */
class Weapon
{
public:
    // Create instance from json tree
    Weapon(pt::ptree params);
    Weapon(const std::string &_id, const IBulletStyle *ibs, const MuzzleFlashStyle *mfs,
           int damage, bool isH) :
            id(_id), bulletStyle(ibs), muzzleFlashStyle(mfs), damage(damage), isHoming(isH) {
        Ogre::LogManager::getSingleton().logMessage("Weapon created");
    }

    Bullet* createBullet(int x, int y, double direction);

    // string identifier used to reference configured instance in json
    std::string id;
    const IBulletStyle *bulletStyle;
    const MuzzleFlashStyle *muzzleFlashStyle;
    int damage;
    bool isHoming;
};

class WeaponException : public std::exception
{
public:
    WeaponException(const std::string m="WeaponException exception was thrown") : msg(m) {}
    virtual ~WeaponException() {}
    virtual const char* what() const noexcept { return msg.c_str(); }

private:
    std::string msg;
};

} // namespace sts
