#pragma once

#include <rendering/sts_renderable.hpp>
#include <gameplay/weaponry/sts_weapon.hpp>

namespace sts {

class UnitType
{
public:
	static UnitType* create(std::string name, Renderable *renderable, int healthM, int speedM, Weapon* w1, Weapon* w2);
	static UnitType* create(std::string name, Renderable *renderable, int healthM, int speedM, std::string weapon1Name, std::string weapon2Name);
	static UnitType* create(std::string name, std::string renderableName, int healthM, int speedM, Weapon* w1, Weapon* w2);
	static UnitType* create(std::string name, std::string renderableName, int healthM, int speedM, std::string weapon1Name, std::string weapon2Name);

	~UnitType();

	std::string name() const;
	Renderable* renderable();
	const Renderable* renderable() const;

	int healthMax() const;
	int speedMax() const;

	Weapon* weapon1();
	const Weapon* weapon1() const;

	Weapon* weapon2();
	const Weapon* weapon2() const;

private:
	std::string _name;
	Renderable* _renderable;
	int _healthMax;
	int _speedMax;
	Weapon* _weapon1;
	Weapon* _weapon2;

	UnitType(std::string name, Renderable *renderable, int healthM, int speedM, Weapon* w1, Weapon* w2);
	UnitType(const UnitType&);
};

} // namespace sts
