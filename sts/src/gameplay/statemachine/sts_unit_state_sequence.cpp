#include "sts_unit_state_sequence.hpp"

namespace sts {

UnitStateSequence::UnitStateSequence()
{
	this->_currentState = this->_states.begin();
}

UnitStateSequence::UnitStateSequence(const UnitStateSequence& uss)
{
	this->reset();
	this->_states = uss._states;
	this->reset();
}

UnitStateSequence::~UnitStateSequence()
{
	while (this->_states.size() > 0) {
		SM::State* state = this->_states.back();
		this->_states.pop_back();
		delete state;
	}
}

void UnitStateSequence::addState(SM::State* state)
{
	if (!state) {
		return;
	}

	bool addState = true;
	for (auto st = this->_states.begin(); st != this->_states.end(); ++st) {
		addState = (*st != state);
		if (!addState) {
			break;
		}
	}

	if (addState) {
		this->_states.push_back(state);
	}
}

std::list<SM::State*> UnitStateSequence::objects()
{
	return this->_states;
}

void UnitStateSequence::removeState(SM::State* state)
{
	if (!state) {
		return;
	}

	bool removeState = false;
	auto st = this->_states.begin();
	for (; st != this->_states.end(); ++st) {
		if (*st != state) {
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
		return *this->_currentState;
	}
}

const SM::State* UnitStateSequence::currentState() const
{
	if (this->_currentState == this->_states.end()) {
		return nullptr;
	} else {
		return *this->_currentState;
	}
}

void UnitStateSequence::reset()
{
	this->_currentState = this->_states.begin();
}

void UnitStateSequence::processState(Unit* unit)
{
	/** @todo Implement this */
}

} // namespace sts
