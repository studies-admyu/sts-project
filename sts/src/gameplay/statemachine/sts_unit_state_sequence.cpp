#include "sts_unit_state_sequence.hpp"

#include <stdexcept>

#include <gameplay/sts_unit.hpp>
#include <gameplay/weaponry/sts_firing_behavior.hpp>

namespace sts {

UnitStateSequence::UnitStateSequence()
{
	this->_currentState = this->_states.begin();
}

UnitStateSequence::UnitStateSequence(const UnitStateSequence& uss)
{
	this->_states.clear();
	this->reset();

	for (auto state = uss._states.cbegin(); state != uss._states.cend(); ++state) {
		this->addState((*state)->makeCopy());
	}

	this->reset();
}

UnitStateSequence::~UnitStateSequence()
{
	while (this->_states.size() > 0) {
		this->_states.pop_back();
	}
}

void UnitStateSequence::updateState(Unit* unit)
{
	if (this->_currentState != this->_states.end()) {
		SM::State* state = this->_currentState->get();
		unit->_setWeapon1FiringState(state->weapon1Behavior()->_createFiringState());
		unit->_setWeapon2FiringState(state->weapon2Behavior()->_createFiringState());
		state->onStateEnter();
		/** @todo Set motion behavior in some manner */
	} else {
		unit->_setWeapon1FiringState(nullptr);
		unit->_setWeapon2FiringState(nullptr);
		unit->_setMotionState(nullptr);
	}
}

void UnitStateSequence::addState(SM::State* state)
{
	if (!state) {
		return;
	}

	bool addState = true;
	for (auto st = this->_states.begin(); st != this->_states.end(); ++st) {
		addState = (st->get() != state);
		if (!addState) {
			break;
		}
	}

	if (addState) {
		this->_states.push_back(std::unique_ptr<SM::State>(state));
	}
}

std::list<SM::State*> UnitStateSequence::objects()
{
	std::list<SM::State*> returnList;
	for (auto state = this->_states.begin(); state != this->_states.end(); ++state) {
		returnList.push_back(state->get());
	}
	return returnList;
}

void UnitStateSequence::removeState(SM::State* state)
{
	if (!state) {
		return;
	}

	bool removeState = false;
	auto st = this->_states.begin();
	for (; st != this->_states.end(); ++st) {
		if (st->get() == state) {
			removeState = true;
			break;
		}
	}
	if (removeState) {
		this->_states.erase(st);
	}
}

SM::State* UnitStateSequence::currentState()
{
	if (this->_currentState == this->_states.end()) {
		return nullptr;
	} else {
		return this->_currentState->get();
	}
}

const SM::State* UnitStateSequence::currentState() const
{
	if (this->_currentState == this->_states.end()) {
		return nullptr;
	} else {
		return this->_currentState->get();
	}
}

void UnitStateSequence::reset()
{
	this->_currentState = this->_states.begin();
}

void UnitStateSequence::processState(Unit* unit)
{
	if (this->_currentState != this->_states.end()) {
		do {
			if (!this->_currentState->get()->checkForTransition(unit)) {
				break;
			}
			/* Take the next state */
			this->_currentState++;
			/* Update unit behavior */
			this->updateState(unit);
		} while (false);
	}
}

} // namespace sts
