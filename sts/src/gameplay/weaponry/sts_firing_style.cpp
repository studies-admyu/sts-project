#include "sts_firing_style.hpp"

#include <stdexcept>

#include "sts_weapon_state.hpp"

namespace sts {

class SingleFiringWeaponState: public WeaponState
{
public:
	SingleFiringWeaponState(Weapon* wp);
	~SingleFiringWeaponState();

	void processFiring(bool firingIsOn);

private:
	SingleFiringWeaponState(const SingleFiringWeaponState&);
};

SingleFiringWeaponState::SingleFiringWeaponState(Weapon* wp)
	: WeaponState(wp)
{

}

SingleFiringWeaponState::SingleFiringWeaponState(const SingleFiringWeaponState&)
	: WeaponState(nullptr)
{
	throw std::runtime_error("SingleFiringWeaponState is not copyable");
}

SingleFiringWeaponState::~SingleFiringWeaponState()
{

}

void SingleFiringWeaponState::processFiring(bool firingIsOn)
{
	/** @todo Implement this */
}


SingleFiringStyle::SingleFiringStyle()
	: _dummy(0)
{

}

SingleFiringStyle::SingleFiringStyle(const SingleFiringStyle&)
{
	throw std::runtime_error("SingleFiringStyle is not copyable");
}

SingleFiringStyle::~SingleFiringStyle()
{

}

WeaponState* SingleFiringStyle::_createWeaponState(Weapon* wp)
{
	return new SingleFiringWeaponState(wp);
}

class ShotgunFiringWeaponState: public WeaponState
{
public:
	ShotgunFiringWeaponState(Weapon* wp);
	~ShotgunFiringWeaponState();

	void processFiring(bool firingIsOn);

private:
	ShotgunFiringWeaponState(const ShotgunFiringWeaponState&);
};

ShotgunFiringWeaponState::ShotgunFiringWeaponState(Weapon* wp)
	: WeaponState(wp)
{

}

ShotgunFiringWeaponState::ShotgunFiringWeaponState(const ShotgunFiringWeaponState&)
	: WeaponState(nullptr)

{
	throw std::runtime_error("ShotgunFiringWeaponState is not copyable");
}

ShotgunFiringWeaponState::~ShotgunFiringWeaponState()
{

}

void ShotgunFiringWeaponState::processFiring(bool firingIsOn)
{
	/** @todo Implement this */
}

ShotgunFiringStyle::ShotgunFiringStyle(float arange, unsigned int cnt)
	: _angleRange(arange), _count(cnt)
{

}

ShotgunFiringStyle::ShotgunFiringStyle(const ShotgunFiringStyle&)
{
	throw std::runtime_error("ShotgunFiringStyle is not copyable");
}

ShotgunFiringStyle::~ShotgunFiringStyle()
{

}

WeaponState* ShotgunFiringStyle::_createWeaponState(Weapon* wp)
{
	return new ShotgunFiringWeaponState(wp);
}

float ShotgunFiringStyle::angleRange() const
{
	return this->_angleRange;
}

unsigned int ShotgunFiringStyle::count() const
{
	return this->_count;
}

class VolleyFiringWeaponState: public WeaponState
{
public:
	VolleyFiringWeaponState(Weapon* wp);
	~VolleyFiringWeaponState();

	void processFiring(bool firingIsOn);

private:
	unsigned int _lastSubShot;
	unsigned int _bulletsProduced;

	VolleyFiringWeaponState(const VolleyFiringWeaponState&);
};

VolleyFiringWeaponState::VolleyFiringWeaponState(Weapon* wp)
	: WeaponState(wp), _lastSubShot(0), _bulletsProduced(0)
{

}

VolleyFiringWeaponState::VolleyFiringWeaponState(const VolleyFiringWeaponState&)
	: WeaponState(nullptr)
{
	throw std::runtime_error("ShotgunFiringStyle is not copyable");
}

VolleyFiringWeaponState::~VolleyFiringWeaponState()
{

}

void VolleyFiringWeaponState::processFiring(bool firingIsOn)
{
	/** @todo Implement this */
}

VolleyFiringStyle::VolleyFiringStyle(unsigned int pd, unsigned int cnt):
	_period(pd), _count(cnt)
{

}

VolleyFiringStyle::VolleyFiringStyle(const VolleyFiringStyle&)
{
	throw std::runtime_error("VolleyFiringStyle is not copyable");
}

VolleyFiringStyle::~VolleyFiringStyle()
{

}

WeaponState* VolleyFiringStyle::_createWeaponState(Weapon* wp)
{
	return new VolleyFiringWeaponState(wp);
}

unsigned int VolleyFiringStyle::period() const
{
	return this->_period;
}

unsigned int VolleyFiringStyle::count() const
{
	return this->_count;
}

} // namespace sts
