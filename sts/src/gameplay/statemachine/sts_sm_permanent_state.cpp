#include "sts_sm_permanent_state.hpp"

#include <stdexcept>

#include <sts_game_root.hpp>
#include <gameplay/motion/sts_motion_behavior.hpp>

namespace sts {

namespace SM {

PermanentState::PermanentState()
{

}

PermanentState::PermanentState(const PermanentState& ps)
	: _mb(ps._mb)
{

}

PermanentState::~PermanentState()
{

}

State* PermanentState::makeCopy() const
{
	return new PermanentState(*this);
}

IMotionBehavior* PermanentState::motionBehavior()
{
	return this->_mb.get();
}

const IMotionBehavior* PermanentState::motionBehavior() const
{
	return this->_mb.get();
}

void PermanentState::setMotionBehavior(IMotionBehavior* mb)
{
	this->_mb = std::shared_ptr<IMotionBehavior>(mb);
}

TimeElapseTransition::TimeElapseTransition(unsigned int timeMsec)
	: _timeMsec(timeMsec), _timeOnTheStart(0)
{

}

TimeElapseTransition::TimeElapseTransition(const TimeElapseTransition&)
{
	throw std::runtime_error("TimeElapseTransition is not copyable");
}

TimeElapseTransition::~TimeElapseTransition()
{

}

ITransition* TimeElapseTransition::makeCopy() const
{
	return new TimeElapseTransition(this->_timeMsec);
}

void TimeElapseTransition::onStateEnter()
{
	this->_timeOnTheStart = sts::GameRoot::getObject()->sceneManager()->_getOTimer()->getMilliseconds();
}

bool TimeElapseTransition::checkForTransition(Unit* unit)
{
	unsigned int currentTime = sts::GameRoot::getObject()->sceneManager()->_getOTimer()->getMilliseconds();
	return (currentTime - this->_timeOnTheStart > this->_timeMsec);
}

HealthElapseTransition::HealthElapseTransition()
{

}

HealthElapseTransition::HealthElapseTransition(const HealthElapseTransition&)
{
	throw std::runtime_error("HealthElapseTransition is not copyable");
}

HealthElapseTransition::~HealthElapseTransition()
{

}

ITransition* HealthElapseTransition::makeCopy() const
{
	return new HealthElapseTransition();
}

void HealthElapseTransition::onStateEnter()
{

}

bool HealthElapseTransition::checkForTransition(Unit* unit)
{
	/** @todo Implement this */
	return false;
}

} // namespace SM

} // namespace sts
