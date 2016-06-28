#pragma once

#include <memory>

#include <scene/sts_layered_object.hpp>

#include "statemachine/sts_unit_state_sequence.hpp"
#include "sts_unit_type.hpp"

namespace sts {

class IFiringState;
class WeaponState;

class Unit: public LayeredObject
{
public:
	static Unit* create(UnitType* utype, unsigned int layerIndex, unsigned int tm, const UnitStateSequence* stSeq);
	static Unit* create(UnitType* utype, Layer* layer, unsigned int tm, const UnitStateSequence* stSeq);
	static Unit* create(std::string unitTypeName, unsigned int layerIndex, unsigned int tm, const UnitStateSequence* stSeq);
	static Unit* create(std::string unitTypeName, Layer* layer, unsigned int tm, const UnitStateSequence* stSeq);

	virtual ~Unit();

	void _setWeapon1FiringState(IFiringState* newState);
	void _setWeapon2FiringState(IFiringState* newState);

	int health() const;
	unsigned int team() const;
	void setHealth(int value);
	void setTeam(unsigned int value);

	UnitType* unitType();
	const UnitType* unitType() const;

	WeaponState* weapon1State();
	const WeaponState* weapon1State() const;
	IFiringState* weapon1FiringState();
	const IFiringState* weapon1FiringState() const;

	WeaponState* weapon2State();
	const WeaponState* weapon2State() const;
	IFiringState* weapon2FiringState();
	const IFiringState* weapon2FiringState() const;

	UnitStateSequence* stateSequence();
	const UnitStateSequence* stateSequence() const;

	virtual void processObject(unsigned int msec);

private:
	Unit(UnitType* utype, Layer* layer, unsigned int tm, const UnitStateSequence* stSeq);
	Unit(UnitType* utype, unsigned int layerIndex, unsigned int tm, const UnitStateSequence* stSeq);
	Unit(const Unit&);

	UnitType* _unitType;
	int _health;
	unsigned int _team;
	bool _isDestructable;
	std::unique_ptr<UnitStateSequence> _stateSequence;
	std::unique_ptr<WeaponState> _weapon1State;
	std::unique_ptr<IFiringState> _weapon1FiringState;
	std::unique_ptr<WeaponState> _weapon2State;
	std::unique_ptr<IFiringState> _weapon2FiringState;

	void initUnit(UnitType* utype, unsigned int tm, const UnitStateSequence* stSeq);
	static UnitStateSequence* createDefaultSequence();
};

} // namespace sts
