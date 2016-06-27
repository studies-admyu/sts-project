#pragma once

namespace sts {

class Unit;

namespace SM {

class ITransition
{
public:
	virtual bool checkForTransition(Unit* unit) = 0;
	/** Virtual destructor to supress warnings */
	virtual ~ITransition() { }
};

} // namespace SM

} // namespace sts
