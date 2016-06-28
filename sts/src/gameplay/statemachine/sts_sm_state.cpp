#include "sts_sm_state.hpp"

#include <gameplay/weaponry/sts_firing_behavior.hpp>

namespace sts {

namespace SM {

State::State()
{

}

State::State(const State& st)
{
	this->_fb1 = st._fb1;
	this->_fb2 = st._fb2;
	for (auto trans = st._transitions.cbegin(); trans != st._transitions.cend(); ++trans) {
		this->_transitions.push_back(std::unique_ptr<ITransition>((*trans)->makeCopy()));
	}
}

State::~State()
{

}

State* State::makeCopy() const
{
	return new State(*this);
}

void State::onStateEnter()
{
	for (auto trans = this->_transitions.begin(); trans != this->_transitions.end(); ++trans) {
		trans->get()->onStateEnter();
	}
}

bool State::checkForTransition(Unit* unit) const
{
	bool makeTransition = false;
	for (auto trans = this->_transitions.cbegin(); trans != this->_transitions.cend(); ++trans) {
		makeTransition = makeTransition || trans->get()->checkForTransition(unit);
		if (makeTransition) {
			break;
		}
	}
	return makeTransition;
}

IFiringBehavior* State::weapon1Behavior()
{
	return this->_fb1.get();
}

const IFiringBehavior* State::weapon1Behavior() const
{
	return this->_fb1.get();
}

void State::setWeapon1Behavior(IFiringBehavior* fb)
{
	this->_fb1.reset(fb);
}

IFiringBehavior* State::weapon2Behavior()
{
	return this->_fb2.get();
}

const IFiringBehavior* State::weapon2Behavior() const
{
	return this->_fb2.get();
}

void State::setWeapon2Behavior(IFiringBehavior* fb)
{
	this->_fb2.reset(fb);
}

void State::addTransition(ITransition* trans)
{
	if (!trans) {
		return;
	}

	bool addTransition = true;
	for (auto tr = this->_transitions.begin(); tr != this->_transitions.end(); ++tr) {
		addTransition = (tr->get() != trans);
		if (!addTransition) {
			break;
		}
	}

	if (addTransition) {
		this->_transitions.push_back(std::unique_ptr<ITransition>(trans));
	}
}

std::list<ITransition*> State::transitions()
{
	std::list<ITransition*> returnList;
	for (auto trans = this->_transitions.begin(); trans != this->_transitions.end(); ++trans) {
		returnList.push_back(trans->get());
	}
	return returnList;
}

void State::removeTransition(ITransition* trans)
{
	if (!trans) {
		return;
	}

	bool removeTransition = false;
	auto tr = this->_transitions.begin();
	for (; tr != this->_transitions.end(); ++tr) {
		if (tr->get() == trans) {
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
