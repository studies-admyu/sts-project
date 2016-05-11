#include "weapon.hpp"

#include "bullet.hpp"
#include "game_data.hpp"

namespace sts {
    Weapon::Weapon(pt::ptree params) {
        std::string bullet_style_name = params.get<std::string>("bullet-style");
        std::string muzzle_flash_style_name = params.get<std::string>("muzzle-flash-style");
        int damage = params.get<int>("damage");
        bool isHoming = params.get<bool>("homing");

        Weapon(id, GameData::bulletStyles[bullet_style_name], GameData::muzzleFlashStyles[muzzle_flash_style_name],
                                 damage, isHoming);
    }

    Bullet* Weapon::createBullet(int x, int y, double direction) {
        Bullet *b = new Bullet(x, y, direction, this);
        return b;
    }

    IWeaponBehaviour* IWeaponBehaviour::createWeaponBehaviour(std::string wb_type, Weapon *w) {
        if (wb_type == "FireForward") {
            return new FireForwardEveryFive(w);
        } else if (wb_type == "NoFire") {
            return new NoFire(w);
        }
        else
            throw WeaponException("Bad weapon behaviour type name");
    }

    bool FireForwardEveryFive::isTimeTofire() {
        double curr_time = 42; // get current gametime
        if (lastShotTime + period >= curr_time) {
            lastShotTime = curr_time;
            return true;
        }
        return false;
    }

}