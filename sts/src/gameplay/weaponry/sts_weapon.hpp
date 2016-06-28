#pragma once

#include <exception>
#include <memory>

#include <boost/property_tree/ptree.hpp>

#include <sts_cross_platform.hpp>

#include "sts_bullet_style.hpp"
#include "sts_firing_style.hpp"
#include "sts_weapon_state.hpp"

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
	static Weapon* create(std::string name, IBulletStyle* bs, IFiringStyle* fs, int dmg, unsigned int cld, bool isHom);
	static Weapon* create(std::string name, pt::ptree params);

	~Weapon();

	std::string name() const;

	IBulletStyle* bulletStyle();
	const IBulletStyle* bulletStyle() const;

	IFiringStyle* firingStyle();
	const IFiringStyle* firingStyle() const;

	int damage() const;
	/** Weapon cooldown (after each shot) in milliseconds. */
	unsigned int cooldown() const;
	bool isHoming() const;

	Bullet* createBullet(int x, int y, double direction);
	WeaponState* createWeaponState();

private:
	std::string _name;
	IBulletStyle* _bulletStyle;
	std::unique_ptr<IFiringStyle> _firingStyle;
	int _damage;
	unsigned int _cooldown;
	bool _isHoming;

	Weapon(std::string name, IBulletStyle* bs, IFiringStyle* fs, int dmg, unsigned int cld, bool isHom);
	Weapon(const Weapon&);
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
