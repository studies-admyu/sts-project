#pragma once

#include <memory>

#include <scene/sts_layered_object.hpp>

#include "statemachine/sts_state.hpp"
#include "sts_unit_type.hpp"

namespace sts {

class IFiringState;
class WeaponState;

class Unit: public LayeredObject
{
public:
	static Unit* create(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<State*> states);
	static Unit* create(std::string renderableName, unsigned int layerIndex, const UnitType* utptr, std::list<State*> states);
	static Unit* create(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<State*> states);
	static Unit* create(std::string renderableName, Layer* layer, const UnitType* utptr, std::list<State*> states);

	virtual ~Unit();

	int health() const;
	unsigned int team() const;
	void setHealth(int value);
	void setTeam(unsigned int value);

	WeaponState* weapon1State();
	const WeaponState* weapon1State() const;
	IFiringState* weapon1FiringState();
	const IFiringState* weapon1FiringState() const;

	WeaponState* weapon2State();
	const WeaponState* weapon2State() const;
	IFiringState* weapon2FiringState();
	const IFiringState* weapon2FiringState() const;

	const UnitType* unitTypePtr;
	std::list<State*> states;

private:
	Unit(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<State*> states);
	Unit(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<State*> states);
	Unit(const Unit&);

	int _health;
	unsigned int _team;
	bool _isDestructable;
	std::unique_ptr<WeaponState> _weapon1State;
	std::unique_ptr<IFiringState> _weapon1FiringState;
	std::unique_ptr<WeaponState> _weapon2State;
	std::unique_ptr<IFiringState> _weapon2FiringState;

	void initUnit(const UnitType* utptr, std::list<State*> states);
};

} // namespace sts
