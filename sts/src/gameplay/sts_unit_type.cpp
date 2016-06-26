#include "sts_unit_type.hpp"

#include <OGRE/OgreRoot.h>

#include <sts_game_root.hpp>

namespace sts {

UnitType::UnitType(std::string name, Renderable *renderable, int healthM, int speedM, Weapon* w1, Weapon* w2)
	: _name(name), _renderable(renderable), _healthMax(healthM), _speedMax(speedM),
	_weapon1(w1), _weapon2(w2)
{
	sts::GameRoot::getObject()->_addUnitType(this);
	Ogre::LogManager::getSingleton().logMessage("UnitType created");
}

UnitType::UnitType(const UnitType&)
{
	throw std::runtime_error("Model3D is not copyable");
}

UnitType::~UnitType()
{

}

UnitType* UnitType::create(std::string name, Renderable *renderable, int healthM, int speedM, Weapon* w1, Weapon* w2)
{
	return new UnitType(name, renderable, healthM, speedM, w1, w2);
}

UnitType* UnitType::create(std::string name, std::string renderableName, int healthM, int speedM, Weapon* w1, Weapon* w2)
{
	return new UnitType(name, sts::GameRoot::getObject()->getRenderable(renderableName), healthM, speedM, w1, w2);
}

std::string UnitType::name() const
{
	return this->_name;
}

Renderable* UnitType::renderable()
{
	return this->_renderable;
}

const Renderable* UnitType::renderable() const
{
	return this->_renderable;
}

int UnitType::healthMax() const
{
	return this->_healthMax;
}

int UnitType::speedMax() const
{
	return this->_speedMax;
}

Weapon* UnitType::weapon1()
{
	return this->_weapon1;
}

const Weapon* UnitType::weapon1() const
{
	return this->_weapon1;
}

Weapon* UnitType::weapon2()
{
	return this->_weapon2;
}

const Weapon* UnitType::weapon2() const
{
	return this->_weapon2;
}

} // namespace sts
