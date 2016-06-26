#include "sts_bullet.hpp"

namespace sts {

void Bullet::move()
{
	weapon->bulletStyle()->move(this);
}

} // namespace sts
