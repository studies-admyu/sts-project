#pragma once

#include <list>
#include <memory>

#include "sts_sm_transition.hpp"

namespace sts {

class IFiringBehavior;

namespace SM {

class State
{
public:
	State();
	virtual ~State();

	virtual State* makeCopy() const;
	virtual void onStateEnter();
	bool checkForTransition(Unit* unit) const;

	IFiringBehavior* weapon1Behavior();
	const IFiringBehavior* weapon1Behavior() const;
	void setWeapon1Behavior(IFiringBehavior* fb);

	IFiringBehavior* weapon2Behavior();
	const IFiringBehavior* weapon2Behavior() const;
	void setWeapon2Behavior(IFiringBehavior* fb);

	virtual void addTransition(ITransition* trans);
	std::list<ITransition*> transitions();
	void removeTransition(ITransition* trans);

protected:
	State(const State&);

private:
	std::shared_ptr<IFiringBehavior> _fb1;
	std::shared_ptr<IFiringBehavior> _fb2;
	std::list<std::unique_ptr<ITransition>> _transitions;
};

} // namespace SM

} // namespace sts
