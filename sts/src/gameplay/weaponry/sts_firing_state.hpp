#pragma once

namespace sts {

class Unit;
class WeaponState;

class IFiringState
{
public:
	virtual void process(Unit* unit, WeaponState* ws) = 0;
	/** Virtual destructor to supress warnings. */
	virtual ~IFiringState() { }
};

} // namespace sts
