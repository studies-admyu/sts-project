#pragma once

#include "game_object.hpp"

namespace sts {

class IMoveBehaviour {
public:
	virtual void move(GameObject &o) = 0;
	// Factory method, chooses child type and creates it.
	// Currently children are hardcoded and not configurable externally. We should change it in the future.
	static IMoveBehaviour* createMoveBehaviour(std::string mb_name);
};

class MoveForward : public IMoveBehaviour {
	double speed;
public:
	virtual void move(GameObject &o) override;
};

class MoveIdle : public IMoveBehaviour {
	virtual void move(GameObject &o) override;
};

class MoveStay : public IMoveBehaviour {
	virtual void move(GameObject &o) override;
};

class MoveBehaviourException : public std::exception {
public:
	MoveBehaviourException(const std::string m="MoveBehaviour exception was thrown") : msg(m) {}
	virtual ~MoveBehaviourException() throw() {}
	virtual const char* what() const noexcept override { return msg.c_str(); }
private:
	std::string msg;
};

}