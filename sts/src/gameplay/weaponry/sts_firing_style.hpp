#pragma once

namespace sts {

class Weapon;
class WeaponState;

class IFiringStyle
{
public:
	virtual WeaponState* _createWeaponState(Weapon* wp) = 0;
};

class SingleFiringStyle: public IFiringStyle
{
public:
	SingleFiringStyle();
	~SingleFiringStyle();

	WeaponState* _createWeaponState(Weapon* wp);

private:
	int _dummy;

	SingleFiringStyle(const SingleFiringStyle&);
};

class ShotgunFiringStyle: public IFiringStyle
{
public:
	ShotgunFiringStyle(float arange, unsigned int cnt);
	~ShotgunFiringStyle();

	WeaponState* _createWeaponState(Weapon* wp);

	float angleRange() const;
	unsigned int count() const;

private:
	float _angleRange;
	unsigned int _count;

	ShotgunFiringStyle(const ShotgunFiringStyle&);
};

class VolleyFiringStyle: public IFiringStyle
{
public:
	VolleyFiringStyle(unsigned int pd, unsigned int cnt);
	~VolleyFiringStyle();

	WeaponState* _createWeaponState(Weapon* wp);

	unsigned int period() const;
	unsigned int count() const;

private:
	unsigned int _period;
	unsigned int _count;

	VolleyFiringStyle(const VolleyFiringStyle&);
};

} // namespace sts
