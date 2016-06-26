#include "sts_weapon.hpp"

#include <OGRE/OgreRoot.h>

#include <sts_game_root.hpp>

namespace sts {

Weapon::Weapon(std::string name, IBulletStyle* bs, IFiringStyle* fs, int dmg, unsigned int cld, bool isHom)
	: _name(name), _bulletStyle(bs), _firingStyle(fs), _damage(dmg), _cooldown(cld), _isHoming(isHom)
{
	sts::GameRoot::getObject()->_addWeapon(this);
	Ogre::LogManager::getSingleton().logMessage("Weapon created");
}

Weapon::Weapon(const Weapon&)
{
	throw std::runtime_error("Weapon is not copyable");
}

Weapon::~Weapon()
{

}

Weapon* Weapon::create(std::string name, IBulletStyle* bs, IFiringStyle* fs, int dmg, unsigned int cld, bool isHom)
{
	return new Weapon(name, bs, fs, dmg, cld, isHom);
}

Weapon* Weapon::create(std::string name, pt::ptree params)
{
	/*
	std::string bullet_style_name = params.get<std::string>("bullet-style");
	std::string firing_style_name = params.get<std::string>("firing-style");
	*/

	int damage = params.get<int>("damage");
	bool isHoming = params.get<bool>("homing");

	/** @todo Fix this */
	return new Weapon(name, nullptr, nullptr, damage, 1000, isHoming);
}

std::string Weapon::name() const
{
	return this->_name;
}

IBulletStyle* Weapon::bulletStyle()
{
	return this->_bulletStyle;
}

const IBulletStyle* Weapon::bulletStyle() const
{
	return this->_bulletStyle;
}

IFiringStyle* Weapon::firingStyle()
{
	return this->_firingStyle;
}

const IFiringStyle* Weapon::firingStyle() const
{
	return this->_firingStyle;
}

int Weapon::damage() const
{
	return this->_damage;
}

unsigned int Weapon::cooldown() const
{
	return this->_cooldown;
}

bool Weapon::isHoming() const
{
	return this->_isHoming;
}

Bullet* Weapon::createBullet(int x, int y, double direction)
{
	/** @todo Implement this */
	/*
	Bullet *b = new Bullet(x, y, direction, this);
	return b;
	*/
	return nullptr;
}

WeaponState* Weapon::createWeaponState()
{
	return this->_firingStyle->_createWeaponState(this);
}

} // namespace sts
