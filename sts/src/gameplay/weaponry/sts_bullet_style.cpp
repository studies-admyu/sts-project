#include "sts_bullet_style.hpp"

namespace sts {

RoundBullet* RoundBullet::instance = nullptr;

RoundBullet* RoundBullet::getInstance()
{
	if (!instance) {
		instance = new RoundBullet();
	}
	return instance;
}

BlastBullet* BlastBullet::instance = nullptr;

BlastBullet* BlastBullet::getInstance()
{
	if (!instance) {
		instance = new BlastBullet();
	}
	return instance;
}

} // namespace sts
