#include "sts_weapon.hpp"

namespace sts {

Weapon::Weapon(pt::ptree params)
{
	std::string bullet_style_name = params.get<std::string>("bullet-style");
	std::string firing_style_name = params.get<std::string>("firing-style");
	int damage = params.get<int>("damage");
	bool isHoming = params.get<bool>("homing");

	Weapon(id, GameData::bulletStyles[bullet_style_name], GameData::firingStyles[firing_style_name],
							 damage, isHoming);
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
