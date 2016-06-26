#include "sts_motion_behavior.hpp"

#include <stdexcept>

#include "sts_motion_state.hpp"

namespace sts {

class MoveIdleState: public IMotionState
{
public:
	MoveIdleState();
	~MoveIdleState();

	void process(SceneObject* obj);

private:
	MoveIdleState(const MoveIdleState&);
};

MoveIdleState::MoveIdleState()
{

}

MoveIdleState::MoveIdleState(const MoveIdleState&)
{
	throw std::runtime_error("MoveIdleState is not copyable");
}

MoveIdleState::~MoveIdleState()
{

}

void MoveIdleState::process(SceneObject* obj)
{
	/** @todo Implement this */
}

MoveIdle::MoveIdle()
{

}

MoveIdle::MoveIdle(const MoveIdle&)
{
	throw std::runtime_error("MoveIdle is not copyable");
}

MoveIdle::~MoveIdle()
{

}

IMotionState* MoveIdle::_createMotionState()
{
	return new MoveIdleState();
}

class MoveStayState: public IMotionState
{
public:
	MoveStayState();
	~MoveStayState();

	void process(SceneObject* obj);

private:
	MoveStayState(const MoveStayState&);
};

MoveStayState::MoveStayState()
{

}

MoveStayState::MoveStayState(const MoveStayState&)
{
	throw std::runtime_error("MoveStayState is not copyable");
}

MoveStayState::~MoveStayState()
{

}

void MoveStayState::process(SceneObject* obj)
{
	/** @todo Implement this */
}

MoveStay::MoveStay()
{

}

MoveStay::MoveStay(const MoveStay&)
{
	throw std::runtime_error("MoveStay is not copyable");
}

MoveStay::~MoveStay()
{

}

IMotionState* MoveStay::_createMotionState()
{
	return new MoveStayState();
}

class MoveForwardState: public IMotionState
{
public:
	MoveForwardState();
	~MoveForwardState();

	void process(SceneObject* obj);

private:
	MoveForwardState(const MoveForwardState&);
};

MoveForwardState::MoveForwardState()
{

}

MoveForwardState::MoveForwardState(const MoveForwardState&)
{
	throw std::runtime_error("MoveForwardState is not copyable");
}

MoveForwardState::~MoveForwardState()
{

}

void MoveForwardState::process(SceneObject* obj)
{
	/** @todo Implement this */
}

MoveForward::MoveForward()
{

}

MoveForward::MoveForward(const MoveForward&)
{
	throw std::runtime_error("MoveForward is not copyable");
}

MoveForward::~MoveForward()
{

}

IMotionState* MoveForward::_createMotionState()
{
	return new MoveForwardState();
}

class MoveByKeysState: public IMotionState
{
public:
	MoveByKeysState(Key mvUpKey, Key mvDownKey, Key mvLeftKey, Key mvRightKey);
	~MoveByKeysState();

	void process(SceneObject* obj);

private:
	MoveByKeysState(const MoveByKeysState&);
};

MoveByKeysState::MoveByKeysState(Key mvUpKey, Key mvDownKey, Key mvLeftKey, Key mvRightKey)
{

}

MoveByKeysState::MoveByKeysState(const MoveByKeysState&)
{
	throw std::runtime_error("MoveForwardState is not copyable");
}

MoveByKeysState::~MoveByKeysState()
{

}

void MoveByKeysState::process(SceneObject* obj)
{
	/** @todo Implement this */
}

MoveByKeys::MoveByKeys(Key mvUpKey, Key mvDownKey, Key mvLeftKey, Key mvRightKey)
{

}

MoveByKeys::MoveByKeys(const MoveByKeys&)
{
	throw std::runtime_error("MoveByKeys is not copyable");
}

MoveByKeys::~MoveByKeys()
{

}

IMotionState* MoveByKeys::_createMotionState()
{
	return new MoveByKeysState(this->_moveUpKey, this->_moveDownKey, this->_moveLeftKey, this->_moveRightKey);
}

} // namespace sts
