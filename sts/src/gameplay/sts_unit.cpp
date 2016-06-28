#include "sts_unit.hpp"

#include <sts_game_root.hpp>

#include "statemachine/sts_sm_permanent_state.hpp"
#include "motion/sts_motion_behavior.hpp"
#include "weaponry/sts_firing_behavior.hpp"
#include "weaponry/sts_firing_state.hpp"
#include "weaponry/sts_weapon_state.hpp"

namespace sts {

Unit::Unit(UnitType* utype, Layer* layer, unsigned int tm, const UnitStateSequence* stSeq)
	: LayeredObject(utype->renderable(), layer)
{
	this->initUnit(utype, tm, stSeq);
}

Unit::Unit(UnitType* utype, unsigned int layerIndex, unsigned int tm, const UnitStateSequence* stSeq)
	: LayeredObject(utype->renderable(), layerIndex)
{
	this->initUnit(utype, tm, stSeq);
}

Unit::Unit(const Unit& unit)
	:LayeredObject(nullptr, nullptr)
{

}

Unit::~Unit()
{

}

void Unit::initUnit(UnitType* utype, unsigned int tm, const UnitStateSequence* stSeq)
{
	if (!stSeq) {
		this->_stateSequence = std::unique_ptr<UnitStateSequence>(Unit::createDefaultSequence());
	} else {
		this->_stateSequence = std::unique_ptr<UnitStateSequence>(new UnitStateSequence(*stSeq));
	}

	this->_unitType = utype;
	if (utype->weapon1()) {
		this->_weapon1State.reset(utype->weapon1()->createWeaponState());
	}
	if (utype->weapon2()) {
		this->_weapon2State.reset(utype->weapon2()->createWeaponState());
	}
	this->_health = utype->healthMax();
	this->_team = tm;
	/** @todo Add isDestructable constructor argument */
	this->_isDestructable = true;
}

UnitStateSequence* Unit::createDefaultSequence()
{
	UnitStateSequence* returnValue = new UnitStateSequence();
	SM::PermanentState* defaultState = new SM::PermanentState();
	defaultState->setWeapon1Behavior(new NoFire());
	defaultState->setWeapon2Behavior(new NoFire());
	defaultState->setMotionBehavior(new MoveIdle());
	returnValue->addState(defaultState);
	return returnValue;
}

Unit* Unit::create(UnitType* utype, unsigned int layerIndex, unsigned int tm, const UnitStateSequence* stSeq)
{
	return new Unit(utype, layerIndex, tm, stSeq);
}

Unit* Unit::create(UnitType* utype, Layer* layer, unsigned int tm, const UnitStateSequence* stSeq)
{
	return new Unit(utype, layer, tm, stSeq);
}

Unit* Unit::create(std::string unitTypeName, unsigned int layerIndex, unsigned int tm, const UnitStateSequence* stSeq)
{
	return new Unit(sts::GameRoot::getObject()->getUnitType(unitTypeName), layerIndex, tm, stSeq);
}

Unit* Unit::create(std::string unitTypeName, Layer* layer, unsigned int tm, const UnitStateSequence* stSeq)
{
	return new Unit(sts::GameRoot::getObject()->getUnitType(unitTypeName), layer, tm, stSeq);
}

void Unit::_setWeapon1FiringState(IFiringState* newState)
{
	this->_weapon1FiringState.reset(newState);
}

void Unit::_setWeapon2FiringState(IFiringState* newState)
{
	this->_weapon2FiringState.reset(newState);
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

UnitType* Unit::unitType()
{
	return this->_unitType;
}

const UnitType* Unit::unitType() const
{
	return this->_unitType;
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

UnitStateSequence* Unit::stateSequence()
{
	return this->_stateSequence.get();
}

const UnitStateSequence* Unit::stateSequence() const
{
	return this->_stateSequence.get();
}

void Unit::processObject(unsigned int msec)
{
	/* Check for the state machine changes */
	this->_stateSequence->processState(this);

	/* Weapon processing */
	if (this->_weapon1FiringState.get() && this->_weapon1State.get()) {
		this->_weapon1FiringState->process(this, this->_weapon1State.get());
	}
	if (this->_weapon2FiringState.get() && this->_weapon2State.get()) {
		this->_weapon2FiringState->process(this, this->_weapon2State.get());
	}

	/* Motion & layer details processing */
	LayeredObject::processObject(msec);
}

} // namespace sts
