#pragma once

#include <list>

#include "sts_transition.hpp"

namespace sts {

class IAimingBehavior;

class State
{
public:
	IAimingBehavior *iab1;
	IAimingBehavior *iab2;
	std::list<Transition> transitions;
};

} // namespace sts
