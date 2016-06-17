#pragma once

#include <gameplay/sts_unit.hpp>

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

namespace sts {

class Weapon;

/**
  * Entry point for SceneObject's active state fire() method. Determines is it time to fire, how many bullets to create
  * and in which direction push them; then it calls weapon.createBullet for each.
  * The class is not jsonified, behaviour is hardcoded.
  * The class needs to store SceneObject's state, at least time of the last shot, so we create an instance for every
  * Unit. Instances will be created by factory method createWeaponBehaviour.
  */
class IAimingBehavior
{
public:
    /** Factory method, creates needed instances on demand */
    static IAimingBehavior* createAimingBehaviour(std::string wb_type, Weapon* w);
    virtual void fire(Unit* u) = 0;

protected:
    virtual bool isTimeTofire() = 0;
    IAimingBehavior(Weapon* w) : weapon(w) {};
    // this weapon will be used to fire
    Weapon* weapon;
};

class FireForwardEveryFive : public IAimingBehavior
{
public:
    FireForwardEveryFive(Weapon* w) : IAimingBehavior(w) {};
    virtual void fire(Unit* u) { /* implement behaviour here */ };

protected:
    virtual bool isTimeTofire();

private:
    double lastShotTime;
    double period;
};

class NoFire : public IAimingBehavior
{
public:
    NoFire(Weapon* w) : IAimingBehavior(w) {};
    virtual void fire(Unit* u) { /* implement behaviour here */ };

protected:
    virtual bool isTimeTofire() { return false; };
};

} // namespace sts
