#include "sts_aiming_behavior.hpp"

namespace sts {

IAimingBehavior* IAimingBehavior::createAimingBehaviour(std::string wb_type, Weapon *w)
{
	if (wb_type == "FireForward") {
		return new FireForwardEveryFive(w);
	} else if (wb_type == "NoFire") {
		return new NoFire(w);
	} else {
		throw WeaponException("Bad weapon behaviour type name");
	}
}

bool FireForwardEveryFive::isTimeTofire()
{
	double curr_time = 42; // get current gametime
	if (lastShotTime + period >= curr_time) {
		lastShotTime = curr_time;
		return true;
	}
	return false;
}

} // namespace sts
