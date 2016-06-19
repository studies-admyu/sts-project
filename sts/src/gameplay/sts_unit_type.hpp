#pragma once

#include <rendering/sts_renderable.hpp>
#include <gameplay/weaponry/sts_weapon.hpp>

namespace sts {

class UnitType
{
public:
	UnitType(std::string id, Renderable *renderablePtr, int hm, int sm, const Weapon *w1, const Weapon *w2);

	std::string id;
	Renderable* renderablePtr;
	int healthMax;
	int speedMax;
	const Weapon *weapon1;
	const Weapon *weapon2;
};

} // namespace sts
