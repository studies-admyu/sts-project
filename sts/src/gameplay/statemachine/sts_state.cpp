#include "sts_state.hpp"

namespace sts {

State::State()
{

}

State::State(const State&)
{

}

State::~State()
{

}

IAimingBehavior* State::weapon1Behavior()
{
	return this->_ab1;
}

const IAimingBehavior* State::weapon1Behavior() const
{
	return this->_ab1;
}

void State::setWeapon1Behavior(IAimingBehavior* ab)
{
	this->_ab1 = ab;
}

IAimingBehavior* State::weapon2Behavior()
{
	return this->_ab2;
}

const IAimingBehavior* State::weapon2Behavior() const
{
	return this->_ab2;
}

void State::setWeapon2Behavior(IAimingBehavior* ab)
{
	this->_ab2 = ab;
}

void State::addTransition(Transition* trans)
{
	if (!trans) {
		return;
	}

	bool addTransition = true;
	for (auto tr = this->_transitions.begin(); tr != this->_transitions.end(); ++tr) {
		addTransition = (*tr != trans);
		if (!addTransition) {
			break;
		}
	}

	if (addTransition) {
		this->_transitions.push_back(trans);
	}
}

std::list<Transition*> State::transitions()
{
	return this->_transitions;
}

void State::removeTransition(Transition* trans)
{
	if (!trans) {
		return;
	}

	bool removeTransition = false;
	auto tr = this->_transitions.begin();
	for (; tr != this->_transitions.end(); ++tr) {
		if (*tr != trans) {
			removeTransition = true;
			break;
		}
	}
	if (removeTransition) {
		this->_transitions.erase(tr);
	}
}

} // namespace sts
