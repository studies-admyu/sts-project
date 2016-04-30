#include "weapon.hpp"

#include "bullet.hpp"

namespace sts {
    Bullet* Weapon::createBullet(int x, int y, double direction) {
        Bullet *b = new Bullet(x, y, direction, this);
    }

    IFiringStyle* Weapon::createNewFiringStyle() const {
        if (firingStyle == "EvenFiringStyle")
            return new EvenFiringStyle();
        else
            throw WeaponException("Bad firing style name");
    }

    bool EvenFiringStyle::isTimeToFire(Unit &u) {
        double curr_time = 42; // get current gametime
        if (lastShotTime + period >= curr_time) {
            lastShotTime = curr_time;
            return true;
        }
        return false;
    }

    IWeaponBehaviour* IWeaponBehaviour::createWeaponBehaviour(std::string wb_type, pt::ptree params) {
        if (wb_type == "FireForward") {
            return new FireForward(params);
        } else if (wb_type == "NoFire") {
            return new NoFire(params);
        }
        else
            throw WeaponException("Bad weapon behaviour type name");
    }
}