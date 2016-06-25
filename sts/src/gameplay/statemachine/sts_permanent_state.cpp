#include "sts_permanent_state.hpp"

namespace sts {

PermanentState::PermanentState()
{

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

TimeElapseTransition::~TimeElapseTransition()
{

}

HealthElapseTransition::HealthElapseTransition()
{

}

HealthElapseTransition::~HealthElapseTransition()
{

}

} // namespace sts
