#include "sts_sm_permanent_state.hpp"

#include <stdexcept>

namespace sts {

namespace SM {

PermanentState::PermanentState()
{

}

PermanentState::PermanentState(const PermanentState&)
{
	throw std::runtime_error("PermanentState is not copyable");
}

PermanentState::~PermanentState()
{

}

IMotionBehavior* PermanentState::motionBehavior()
{
	return this->_mb;
}

const IMotionBehavior* PermanentState::motionBehavior() const
{
	return this->_mb;
}

void PermanentState::setMotionBehavior(IMotionBehavior* mb)
{
	this->_mb = mb;
}

TimeElapseTransition::TimeElapseTransition()
{

}

TimeElapseTransition::TimeElapseTransition(const TimeElapseTransition&)
{
	throw std::runtime_error("TimeElapseTransition is not copyable");
}

TimeElapseTransition::~TimeElapseTransition()
{

}

bool TimeElapseTransition::checkForTransition(Unit* unit)
{
	/** @todo Implement this */
	return false;
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

bool HealthElapseTransition::checkForTransition(Unit* unit)
{
	/** @todo Implement this */
	return false;
}

} // namespace SM

} // namespace sts
