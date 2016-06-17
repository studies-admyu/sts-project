#include "sts_unit.hpp"

namespace sts {

Unit::Unit(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<State*> _states)
	:LayeredObject(renderable, layerIndex)
{
	unitTypePtr = utptr;
	states = _states;
}

Unit::Unit(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<State*> _states)
	:LayeredObject(renderable, layer)
{
	unitTypePtr = utptr;
	states = _states;
}

} // namespace sts
