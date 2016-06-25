#pragma once

#include <list>

#include "sts_transition.hpp"

namespace sts {

class IAimingBehavior;

class State
{
public:
	State();
	State(const State&);
	virtual ~State();

	IAimingBehavior* weapon1Behavior();
	const IAimingBehavior* weapon1Behavior() const;
	void setWeapon1Behavior(IAimingBehavior* ab);

	IAimingBehavior* weapon2Behavior();
	const IAimingBehavior* weapon2Behavior() const;
	void setWeapon2Behavior(IAimingBehavior* ab);

	virtual void addTransition(Transition* trans);
	std::list<Transition*> transitions();
	void removeTransition(Transition* trans);

private:
	IAimingBehavior* _ab1;
	IAimingBehavior* _ab2;
	std::list<Transition*> _transitions;
};

} // namespace sts
