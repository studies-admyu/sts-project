#include "sts_weapon_state.hpp"

#include <sts_game_root.hpp>

namespace sts {

WeaponState::WeaponState(Weapon* wp)
	: _lastShot(0), _weapon(wp)
{

}

WeaponState::WeaponState(const WeaponState&)
{

}

WeaponState::~WeaponState()
{

}

unsigned int WeaponState::lastShot() const
{
	return this->_lastShot;
}

void WeaponState::shot()
{
	this->_lastShot = sts::GameRoot::getObject()->sceneManager()->_getOTimer()->getMilliseconds();
}

void WeaponState::processFiring(bool firingIsOn)
{
	/** @todo Implement this */
}

Weapon* WeaponState::weapon()
{
	return this->_weapon;
}

const Weapon* WeaponState::weapon() const
{
	return this->_weapon;
}

} // namespace sts
