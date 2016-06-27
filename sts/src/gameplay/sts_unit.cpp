#include "sts_unit.hpp"

#include <sts_game_root.hpp>

#include "weaponry/sts_firing_state.hpp"
#include "weaponry/sts_weapon_state.hpp"

namespace sts {

Unit::Unit(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<SM::State*> _states)
	:LayeredObject(renderable, layerIndex)
{
	this->initUnit(utptr, _states);
}

Unit::Unit(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<SM::State*> _states)
	:LayeredObject(renderable, layer)
{
	this->initUnit(utptr, _states);
}

Unit::Unit(const Unit& unit)
	:LayeredObject(nullptr, nullptr)
{

}

Unit::~Unit()
{

}

void Unit::initUnit(const UnitType* utptr, std::list<SM::State*> states)
{
	this->unitTypePtr = utptr;
	this->states = states;
	this->_health = 100;
	this->_team = 0;
	this->_isDestructable = true;
}

Unit* Unit::create(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<SM::State*> states)
{
	return new Unit(renderable, layerIndex, utptr, states);
}

Unit* Unit::create(std::string renderableName, unsigned int layerIndex, const UnitType* utptr, std::list<SM::State*> states)
{
	return new Unit(sts::GameRoot::getObject()->getRenderable(renderableName), layerIndex, utptr, states);
}

Unit* Unit::create(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<SM::State*> states)
{
	return new Unit(renderable, layer, utptr, states);
}

Unit* Unit::create(std::string renderableName, Layer* layer, const UnitType* utptr, std::list<SM::State*> states)
{
	return new Unit(sts::GameRoot::getObject()->getRenderable(renderableName), layer, utptr, states);
}

int Unit::health() const
{
	return this->_health;
}

unsigned int Unit::team() const
{
	return this->_team;
}

void Unit::setHealth(int value)
{
	this->_health = value;
}

void Unit::setTeam(unsigned int value)
{
	this->_team = value;
}

WeaponState* Unit::weapon1State()
{
	return this->_weapon1State.get();
}

const WeaponState* Unit::weapon1State() const
{
	return this->_weapon1State.get();
}

IFiringState* Unit::weapon1FiringState()
{
	return this->_weapon1FiringState.get();
}

const IFiringState* Unit::weapon1FiringState() const
{
	return this->_weapon1FiringState.get();
}

WeaponState* Unit::weapon2State()
{
	return this->_weapon2State.get();
}

const WeaponState* Unit::weapon2State() const
{
	return this->_weapon2State.get();
}

IFiringState* Unit::weapon2FiringState()
{
	return this->_weapon2FiringState.get();
}

const IFiringState* Unit::weapon2FiringState() const
{
	return this->_weapon2FiringState.get();
}

} // namespace sts
