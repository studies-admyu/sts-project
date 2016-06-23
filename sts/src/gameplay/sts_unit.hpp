#pragma once

#include <scene/sts_layered_object.hpp>

#include "statemachine/sts_state.hpp"
#include "sts_unit_type.hpp"

namespace sts {

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

	const UnitType* unitTypePtr;
	std::list<State*> states;

private:
	Unit(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<State*> states);
	Unit(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<State*> states);
	Unit(const Unit&);

	int _health;
	unsigned int _team;
	bool _isDestructable;

	void initUnit(const UnitType* utptr, std::list<State*> states);
};

} // namespace sts
