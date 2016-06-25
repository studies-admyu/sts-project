#pragma once

#include "sts_state.hpp"

namespace sts {

class IMotionBehavior;

class PermanentState: public State
{
	PermanentState();
	~PermanentState();

	IMotionBehavior* motionBehavior();
	const IMotionBehavior* motionBehavior() const;
	void setMotionBehavior(IMotionBehavior* mb);

private:
	IMotionBehavior* _mb;
};

class TimeElapseTransition: public Transition
{
public:
	TimeElapseTransition();
	~TimeElapseTransition();
};

class HealthElapseTransition: public Transition
{
public:
	HealthElapseTransition();
	~HealthElapseTransition();
};

} // namespace sts
