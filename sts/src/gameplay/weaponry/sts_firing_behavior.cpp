#include "sts_firing_behavior.hpp"

#include <stdexcept>

#include "sts_firing_state.hpp"

namespace sts {

class NoFireState: public IFiringState
{
public:
	NoFireState();
	~NoFireState();

	void process(Unit* unit, WeaponState* ws);

private:
	int _dummy;

	NoFireState(const NoFireState&);
};

NoFireState::NoFireState()
	: _dummy(0)
{

}

NoFireState::NoFireState(const NoFireState&)
{
	throw std::runtime_error("NoFireState is not copyable");
}

NoFireState::~NoFireState()
{

}

void NoFireState::process(Unit* unit, WeaponState* ws)
{
	/** @todo Implement this */
}

NoFire::NoFire()
{

}

NoFire::NoFire(const NoFire&)
{
	throw std::runtime_error("NoFire is not copyable");
}

NoFire::~NoFire()
{

}

IFiringState* NoFire::_createFiringState()
{
	return new NoFireState();
}

class FireForwardState: public IFiringState
{
public:
	FireForwardState();
	~FireForwardState();

	void process(Unit* unit, WeaponState* ws);

private:
	int _dummy;

	FireForwardState(const FireForwardState&);
};

FireForwardState::FireForwardState()
	: _dummy(0)
{

}

FireForwardState::FireForwardState(const FireForwardState&)
{
	throw std::runtime_error("FireForwardState is not copyable");
}

FireForwardState::~FireForwardState()
{

}

void FireForwardState::process(Unit* unit, WeaponState* ws)
{
	/** @todo Implement this */
}

FireForward::FireForward()
{

}

FireForward::FireForward(const FireForward&)
{
	throw std::runtime_error("FireForward is not copyable");
}

FireForward::~FireForward()
{

}

IFiringState* FireForward::_createFiringState()
{
	return new FireForwardState();
}

class FireNearestEnemiesState: public IFiringState
{
public:
	FireNearestEnemiesState();
	~FireNearestEnemiesState();

	void process(Unit* unit, WeaponState* ws);

private:
	int _dummy;

	FireNearestEnemiesState(const FireNearestEnemiesState&);
};

FireNearestEnemiesState::FireNearestEnemiesState()
	: _dummy(0)
{

}

FireNearestEnemiesState::FireNearestEnemiesState(const FireNearestEnemiesState&)
{
	throw std::runtime_error("FireNearestEnemiesState is not copyable");
}

FireNearestEnemiesState::~FireNearestEnemiesState()
{

}

void FireNearestEnemiesState::process(Unit* unit, WeaponState* ws)
{
	/** @todo Implement this */
}

FireNearestEnemies::FireNearestEnemies()
{

}

FireNearestEnemies::FireNearestEnemies(const FireNearestEnemies&)
{
	throw std::runtime_error("FireNearestEnemies is not copyable");
}

FireNearestEnemies::~FireNearestEnemies()
{

}

IFiringState* FireNearestEnemies::_createFiringState()
{
	return new FireNearestEnemiesState();
}

class FireByKeyState: public IFiringState
{
public:
	FireByKeyState(sts::Key fireKey);
	~FireByKeyState();

	void process(Unit* unit, WeaponState* ws);

private:
	sts::Key _fireKey;

	FireByKeyState(const FireByKeyState&);
};

FireByKeyState::FireByKeyState(sts::Key fireKey)
	: _fireKey(fireKey)
{

}

FireByKeyState::FireByKeyState(const FireByKeyState&)
{
	throw std::runtime_error("FireByKeyState is not copyable");
}

FireByKeyState::~FireByKeyState()
{

}

void FireByKeyState::process(Unit* unit, WeaponState* ws)
{
	/** @todo Implement this */
}

FireByKey::FireByKey(Key fireKey)
	: _fireKey(fireKey)
{

}

FireByKey::FireByKey(const FireByKey&)
{
	throw std::runtime_error("FireByKey is not copyable");
}

FireByKey::~FireByKey()
{

}

IFiringState* FireByKey::_createFiringState()
{
	return new FireByKeyState(this->_fireKey);
}

} // namespace sts
