#pragma once

#include "sts_state.hpp"

namespace sts {

class UnitStateSequence
{
public:
	UnitStateSequence();
	UnitStateSequence(const UnitStateSequence&);
	~UnitStateSequence();

	void addState(State* state);
	std::list<State*> objects();
	void removeState(State* state);

	State* currentState();
	const State* currentState() const;
	void reset();

private:
	std::list<State*> _states;
	std::list<State*>::iterator _currentState;
};

} // namespace sts
