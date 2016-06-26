#include "sts_weapon.hpp"

#include <OGRE/OgreRoot.h>

#include <sts_game_root.hpp>

namespace sts {

Weapon::Weapon(std::string name, IBulletStyle* bs, FiringStyle* fs, int dmg, bool isHom)
	: _name(name), _bulletStyle(bs), _firingStyle(fs), _damage(dmg), _isHoming(isHom)
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

Weapon* Weapon::create(std::string name, IBulletStyle* bs, FiringStyle* fs, int dmg, bool isHom)
{
	return new Weapon(name, bs, fs, dmg, isHom);
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
	return new Weapon(name, nullptr, nullptr, damage, isHoming);
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

FiringStyle* Weapon::firingStyle()
{
	return this->_firingStyle;
}

const FiringStyle* Weapon::firingStyle() const
{
	return this->_firingStyle;
}

int Weapon::damage() const
{
	return this->_damage;
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

} // namespace sts
