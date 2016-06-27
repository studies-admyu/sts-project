#pragma once

#include <list>

#include "sts_sm_transition.hpp"

namespace sts {

class IFiringBehavior;

namespace SM {

class State
{
public:
	State();
	State(const State&);
	virtual ~State();

	IFiringBehavior* weapon1Behavior();
	const IFiringBehavior* weapon1Behavior() const;
	void setWeapon1Behavior(IFiringBehavior* fb);

	IFiringBehavior* weapon2Behavior();
	const IFiringBehavior* weapon2Behavior() const;
	void setWeapon2Behavior(IFiringBehavior* fb);

	virtual void addTransition(ITransition* trans);
	std::list<ITransition*> transitions();
	void removeTransition(ITransition* trans);

private:
	IFiringBehavior* _ab1;
	IFiringBehavior* _ab2;
	std::list<ITransition*> _transitions;
};

} // namespace SM

} // namespace sts
