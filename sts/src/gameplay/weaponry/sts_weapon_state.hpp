#pragma once

namespace sts {

class Weapon;

class WeaponState
{
public:
	virtual ~WeaponState();

	/** Last shot time in milliseconds. */
	unsigned int lastShot() const;
	/** Updates the last shot time. */
	void shot();

	virtual void processFiring(bool firingIsOn);

	Weapon* weapon();
	const Weapon* weapon() const;

protected:
	WeaponState(Weapon* wp);

private:
	unsigned int _lastShot;
	Weapon* _weapon;

	WeaponState(const WeaponState&);
};

} // namespace sts
