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
 *     - WeaponBehaviour checks, whether time for firing has come;
 *     - If it is, WeaponBehaviour determines number of bullets and their direction
 *       (hardcoded in descendants, not jsonified)
 *     - For each bullet to fire, it runs weapon.createBullet method
 */

struct MuzzleFlashStyle {
    MuzzleFlashStyle(const std::string &_id, const std::string &_colormap_hue, const std::string &_sound)
            : id(_id), colormap_hue(_colormap_hue), sound(_sound) {}
    std::string id;
    /* convert to hex immediately? */
    std::string colormap_hue;
    std::string sound;
};

/*
 * Weapon defines information about weapon: it' damage, BulletStyle, animations, etc, but it doesn't make
 * decisions when and where to shot. It also creates bullets.
 * It is jsonified, but each weapon is instantiated only once since it doesn't need SceneObject specific state
 */
class Weapon {
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

/*
 * Entry point for SceneObject's active state fire() method. Determines is it time to fire, how many bullets to create
 * and in which direction push them; then it calls weapon.createBullet for each.
 * The class is not jsonified, behaviour is hardcoded.
 * The class needs to store SceneObject's state, at least time of the last shot, so we create an instance for every
 * Unit. Instances will be created by factory method createWeaponBehaviour.
 * */
class IWeaponBehaviour {
public:
    /*
     * Factory method, creates needed instances on demand
     * */
    static IWeaponBehaviour* createWeaponBehaviour(std::string wb_type, Weapon *w);
    virtual void fire(Unit *u) = 0;
protected:
    virtual bool isTimeTofire() = 0;
    IWeaponBehaviour(Weapon *w) : weapon(w) {};
    // this weapon will be used to fire
    Weapon *weapon;
};

class FireForwardEveryFive : public IWeaponBehaviour {
public:
    FireForwardEveryFive(Weapon *w) : IWeaponBehaviour(w) {};
    virtual void fire(Unit *u) { /* implement behaviour here */ };
protected:
    virtual bool isTimeTofire();
private:
    double lastShotTime;
    double period;
};

class NoFire : public IWeaponBehaviour {
public:
    NoFire(Weapon *w) : IWeaponBehaviour(w) {};
    virtual void fire(Unit *u) { /* implement behaviour here */ };
protected:
    virtual bool isTimeTofire() { return false; };
};


class WeaponException : public std::exception {
public:
    WeaponException(const std::string m="WeaponException exception was thrown") : msg(m) {}
    virtual ~WeaponException() {}
    virtual const char* what() const { return msg.c_str(); }
private:
    std::string msg;
};

}

