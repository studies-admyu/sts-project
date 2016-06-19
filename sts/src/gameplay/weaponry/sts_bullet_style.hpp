#pragma once

#include <OGRE/OgreRoot.h>

#include <rendering/sts_renderable.hpp>
#include <scene/sts_scene_object.hpp>
#include <game_data.hpp>

namespace sts {

class Bullet;

/**
  * Specifies how a bullet looks like, how it moves and how it handles collisions.
  * All BulletStyles are singltones with hardcoded behaviours.
  * Creates bullets of this style on demand.
  */
class IBulletStyle
{
public:
	IBulletStyle(const Renderable *r) : renderablePtr(r) {}
	// Every bullet style must decide how to handle collisions.
	virtual void collisionAlgorithm(SceneObject& o) const = 0;
	// Every bullet style must decide how to move the bullet
	virtual void move(Bullet *bullet) const = 0;

protected:
	const Renderable* renderablePtr;
};

class RoundBullet: public IBulletStyle
{
public:
	static RoundBullet* getInstance();
	virtual void collisionAlgorithm(SceneObject& o) const { /* handle collision here */ }
	virtual void move(Bullet *bullet) const { return Ogre::LogManager::getSingleton().logMessage("Moving RoundBullet"); }

private:
	RoundBullet() : IBulletStyle(GameData::renderables["RoundBullet"]) { Ogre::LogManager::getSingleton().logMessage("RoundBullet style created");}
	RoundBullet(RoundBullet const&): IBulletStyle(GameData::renderables["RoundBullet"]) { };
	RoundBullet& operator=(RoundBullet const&) { return *this; };
	static RoundBullet *instance;
};

class BlastBullet: public IBulletStyle
{
public:
	static BlastBullet* getInstance();
	virtual void collisionAlgorithm(SceneObject& o) const { /* handle collision here */ }
	virtual void move(Bullet *bullet) const { return Ogre::LogManager::getSingleton().logMessage("Moving BlastBullet"); }

private:
	BlastBullet() : IBulletStyle(GameData::renderables["BlastBullet"]) { Ogre::LogManager::getSingleton().logMessage("BlastBullet style created");}
	BlastBullet(BlastBullet const&): IBulletStyle(GameData::renderables["BlastBullet"]) { }
	BlastBullet& operator=(BlastBullet const&) { return *this; }
	static BlastBullet *instance;
};

} // namespace sts
