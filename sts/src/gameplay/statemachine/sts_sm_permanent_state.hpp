#pragma once

#include "sts_sm_state.hpp"

namespace sts {

class IMotionBehavior;

namespace SM {

class PermanentState: public State
{
public:
	PermanentState();
	~PermanentState();

	State* makeCopy() const;

	IMotionBehavior* motionBehavior();
	const IMotionBehavior* motionBehavior() const;
	void setMotionBehavior(IMotionBehavior* mb);

protected:
	PermanentState(const PermanentState&);

private:
	std::shared_ptr<IMotionBehavior> _mb;
};

class TimeElapseTransition: public ITransition
{
public:
	TimeElapseTransition(unsigned int timeMsec);
	~TimeElapseTransition();

	ITransition* makeCopy() const;
	void onStateEnter();
	bool checkForTransition(Unit* unit);

private:
	unsigned int _timeMsec;
	unsigned int _timeOnTheStart;

	TimeElapseTransition(const TimeElapseTransition&);
};

class HealthElapseTransition: public ITransition
{
public:
	HealthElapseTransition();
	~HealthElapseTransition();

	ITransition* makeCopy() const;
	void onStateEnter();
	bool checkForTransition(Unit* unit);

private:
	HealthElapseTransition(const HealthElapseTransition&);
};

} // namespace SM

} // namespace sts
