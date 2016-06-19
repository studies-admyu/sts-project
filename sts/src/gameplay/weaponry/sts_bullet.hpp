#pragma once

#include <OGRE/OgreRoot.h>

#include <scene/sts_shared_object.hpp>
#include <gameplay/weaponry/sts_weapon.hpp>

namespace sts {

class Bullet: public SharedObject
{
public:
	Bullet(Renderable* renderable, Weapon* w): SharedObject(renderable), weapon(w) {}
	void move();

private:
	Weapon *weapon;
};

} // namespace sts
