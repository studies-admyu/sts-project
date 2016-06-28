#include "sts_bullet_style.hpp"

#include <stdexcept>

#include <OGRE/OgreRoot.h>

namespace sts {

RoundBulletStyle* mRoundBulletStyle = nullptr;

RoundBulletStyle::RoundBulletStyle()
{
	Ogre::LogManager::getSingleton().logMessage("RoundBulletStyle created.");
}

RoundBulletStyle::RoundBulletStyle(const RoundBulletStyle&)
{
	throw std::runtime_error("RoundBulletStyle is a singleton and can't be copied.");
}

RoundBulletStyle::~RoundBulletStyle()
{

}

RoundBulletStyle* RoundBulletStyle::getObject()
{
	if (!mRoundBulletStyle) {
		mRoundBulletStyle = new RoundBulletStyle();
	}
	return mRoundBulletStyle;
}

void RoundBulletStyle::releaseObject()
{
	if (mRoundBulletStyle) {
		delete mRoundBulletStyle;
		mRoundBulletStyle = nullptr;
	}
}

Bullet* RoundBulletStyle::_createBullet(SceneObject::Position pos)
{
	/** @todo Implement this */
	return nullptr;
}

BlastBulletStyle::BlastBulletStyle()
{
	Ogre::LogManager::getSingleton().logMessage("BlastBulletStyle created.");
}

BlastBulletStyle::BlastBulletStyle(const BlastBulletStyle&)
{
	throw std::runtime_error("BlastBulletStyle is a singleton and can't be copied.");
}

BlastBulletStyle::~BlastBulletStyle()
{

}

BlastBulletStyle* mBlastBulletStyle = nullptr;

BlastBulletStyle* BlastBulletStyle::getObject()
{
	if (!mBlastBulletStyle) {
		mBlastBulletStyle = new BlastBulletStyle();
	}
	return mBlastBulletStyle;
}

void BlastBulletStyle::releaseObject()
{
	if (mBlastBulletStyle) {
		delete mBlastBulletStyle;
		mBlastBulletStyle = nullptr;
	}
}

Bullet* BlastBulletStyle::_createBullet(SceneObject::Position pos)
{
	/** @todo Implement this */
	return nullptr;
}

} // namespace sts
