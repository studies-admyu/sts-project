#include "bullet.hpp"
#include "weapon.hpp"

namespace sts {
    void Bullet::move() {weapon->bulletStylePtr->move(this); }

    RoundBullet* RoundBullet::instance = nullptr;
    RoundBullet* RoundBullet::getInstance() {
        if (!instance)
            instance = new RoundBullet();
        return instance;
    }

    BlastBullet* BlastBullet::instance = nullptr;
    BlastBullet* BlastBullet::getInstance() {
        if (!instance)
            instance = new BlastBullet();
        return instance;
    }

}