#pragma once

#include <OGRE/OgreRoot.h>
#include <boost/property_tree/ptree.hpp>

#include <string>
#include "bullet.hpp"
#include "game_object.hpp"

namespace sts {
    namespace pt = boost::property_tree;

/*
 * The whole process of firing:
 *   * from main cycle method fire of Unit is called
 *   * from it's active state, for each weaponBehaviour:
 *     - call weaponBehaviour.fire()
 *     - it checks, if time for firing has come by running
 */

struct MuzzleFlashStyle {
    MuzzleFlashStyle(const std::string &_id, const std::string &_colormap_hue, const std::string &_sound)
            : id(_id), colormap_hue(_colormap_hue), sound(_sound) {}
    std::string id;
    /* convert to hex immediately? */
    std::string colormap_hue;
    std::string sound;
};

// Weapon defines information about weapon: it' damage, bullet, animations, etc, but it doesn't make
// decisions when and where to shot. It also creates bullets.
class Weapon {
public:
    Weapon(const std::string &_id, const IBulletStyle *ibs, const MuzzleFlashStyle *mfs,
           int d, bool isH, std::string fs) :
            id(_id), bulletStylePtr(ibs), muzzleFlashStylePtr(mfs), damage(d), isHoming(isH), firingStyle(fs) {
        Ogre::LogManager::getSingleton().logMessage("Weapon created");
    }

    Bullet* createBullet(int x, int y, double direction);
    IFiringStyle* createNewFiringStyle() const;

    std::string id;
    std::string firingStyle;
    const IBulletStyle *bulletStylePtr;
    const MuzzleFlashStyle *muzzleFlashStylePtr;
    int damage;
    bool isHoming;
};

// Entry point for fire(); Asks FiringStyle, is it time to fire, then defines number and direction of bullets and
// finally calls createBullet of Weapon
class IWeaponBehaviour {
public:
    static IWeaponBehaviour* createWeaponBehaviour(std::string wb_type, pt::ptree params);
    virtual void behaviourAlgorithm(Unit &u) = 0;
};

class FireForward : public IWeaponBehaviour {
public:
    FireForward(pt::ptree params) { count = params.get<int>("count"); period = params.get<double>("period"); };
    virtual void behaviourAlgorithm(Unit &u) { /* implement behaviour here */ };
private:
    int count;
    double period;
};

class NoFire : public IWeaponBehaviour {
public:
    NoFire(pt::ptree params) {}
    virtual void behaviourAlgorithm(Unit &u) { /* implement behaviour here */ };
};

class IFiringStyle {
public:
    virtual bool isTimeToFire(Unit &u) = 0;
};

class EvenFiringStyle : public IFiringStyle {
public:
    virtual bool isTimeToFire(Unit &u) override;
private:
    const int period = 5;
    double lastShotTime = 0;
};

class WeaponException : public std::exception {
public:
    WeaponException(const std::string m="WeaponException exception was thrown") : msg(m) {}
    virtual ~WeaponException() throw() {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

}

