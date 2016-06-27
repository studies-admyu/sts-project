#pragma once

#include "sts_sm_state.hpp"

namespace sts {

class UnitStateSequence
{
public:
	UnitStateSequence();
	UnitStateSequence(const UnitStateSequence&);
	~UnitStateSequence();

	void addState(SM::State* state);
	std::list<SM::State*> objects();
	void removeState(SM::State* state);

	SM::State* currentState();
	const SM::State* currentState() const;
	void reset();

	void processState(Unit* unit);

private:
	std::list<SM::State*> _states;
	std::list<SM::State*>::iterator _currentState;
};

} // namespace sts
