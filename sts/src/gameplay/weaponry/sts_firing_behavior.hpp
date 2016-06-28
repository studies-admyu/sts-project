#pragma once

#include <gameplay/sts_unit.hpp>
#include <input/sts_key.hpp>

/*
 * The whole process of firing:
 *   * create FiringBehavior (with parameters if necessary)
 *   * call FiringBehavior::_createFiringState which creates an algorith & data struct
 *   * take the FiringState which was returned and give it to unit
 *   * from main cycle method process() of Unit is called
 *   * from it's active state, for each FiringState:
 *     - call FiringState::process()
 *     - FiringState checks for aims or direction to fire (according to the data that is
 *       unique for every unit & state);
 *     - If fire is necessary, FiringState calls WeaponState::processFiring()
 *     - Concrete WeaponState inherit determines period, direction and number of bullets
 *     - For each bullet to fire, WeaponState runs Weapon::createBullet method
 */

namespace sts {

class IFiringState;
class Weapon;

/**
  * Entry point for SceneObject's active state fire() method. Determines is it time to fire, how many bullets to create
  * and in which direction push them; then it calls weapon.createBullet for each.
  * The class is not jsonified, behaviour is hardcoded.
  * The class needs to store SceneObject's state, at least time of the last shot, so we create an instance for every
  * Unit. Instances will be created by factory method createWeaponBehaviour.
  */
class IFiringBehavior
{
public:
	virtual IFiringState* _createFiringState() = 0;
	/** Virtual destructor to supress warnings. */
	virtual ~IFiringBehavior() { }
};

class NoFire: public IFiringBehavior
{
public:
	NoFire();
	~NoFire();

	IFiringState* _createFiringState();

private:
	NoFire(const NoFire&);
};

class FireForward: public IFiringBehavior
{
public:
	FireForward();
	~FireForward();

	IFiringState* _createFiringState();

private:
	FireForward(const FireForward&);
};

class FireNearestEnemies: public IFiringBehavior
{
public:
	FireNearestEnemies();
	~FireNearestEnemies();

	IFiringState* _createFiringState();

private:
	FireNearestEnemies(const FireNearestEnemies&);
};

class FireByKey: public IFiringBehavior
{
public:
	FireByKey(Key fireKey);
	~FireByKey();

	IFiringState* _createFiringState();

private:
	Key _fireKey;

	FireByKey(const FireByKey&);
};

} // namespace sts
