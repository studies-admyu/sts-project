#pragma once

#include "sts_sm_state.hpp"

namespace sts {

class IMotionBehavior;

namespace SM {

class PermanentState: public State
{
	PermanentState();
	~PermanentState();

	IMotionBehavior* motionBehavior();
	const IMotionBehavior* motionBehavior() const;
	void setMotionBehavior(IMotionBehavior* mb);

private:
	IMotionBehavior* _mb;

	PermanentState(const PermanentState&);
};

class TimeElapseTransition: public ITransition
{
public:
	TimeElapseTransition();
	~TimeElapseTransition();

	bool checkForTransition(Unit* unit);

private:
	TimeElapseTransition(const TimeElapseTransition&);
};

class HealthElapseTransition: public ITransition
{
public:
	HealthElapseTransition();
	~HealthElapseTransition();

	bool checkForTransition(Unit* unit);

private:
	HealthElapseTransition(const HealthElapseTransition&);
};

} // namespace SM

} // namespace sts
