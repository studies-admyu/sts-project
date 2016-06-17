#pragma once

#include <scene/sts_layered_object.hpp>

#include "statemachine/sts_state.hpp"
#include "sts_unit_type.hpp"

namespace sts {

class Unit: public LayeredObject
{
public:
	Unit(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<State*> states);
	Unit(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<State*> states);
	const UnitType* unitTypePtr;
	std::list<State*> states;
};

} // namespace sts
