#include "sts_sm_state.hpp"

namespace sts {

namespace SM {

State::State()
{

}

State::State(const State&)
{

}

State::~State()
{

}

IFiringBehavior* State::weapon1Behavior()
{
	return this->_ab1;
}

const IFiringBehavior* State::weapon1Behavior() const
{
	return this->_ab1;
}

void State::setWeapon1Behavior(IFiringBehavior* ab)
{
	this->_ab1 = ab;
}

IFiringBehavior* State::weapon2Behavior()
{
	return this->_ab2;
}

const IFiringBehavior* State::weapon2Behavior() const
{
	return this->_ab2;
}

void State::setWeapon2Behavior(IFiringBehavior* ab)
{
	this->_ab2 = ab;
}

void State::addTransition(ITransition* trans)
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

std::list<ITransition*> State::transitions()
{
	return this->_transitions;
}

void State::removeTransition(ITransition* trans)
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

} // namespace SM

} // namespace sts
